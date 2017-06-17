//
// Created by garik on 27.05.17.
//

#include "ConnectExecutor.h"

#include <sys/socket.h>

#if linux

#include <sys/epoll.h>
#include <unistd.h>

#elif __APPLE__
#endif


ConnectExecutor::ConnectExecutor(unsigned int count, unsigned int threadCount)
        : size(count), responseExecutor(threadCount) {
    requestExecutor = std::thread(&ConnectExecutor::add_socket_impl, this);
#if linux
    epoll_fd = epoll_create(size);
    countNow = 0;
#elif __APPLE__
#endif
}

ConnectExecutor::~ConnectExecutor() {
    {
        std::lock_guard<std::mutex> l(mutex);
        shouldQuit = true;
    }
    while (!isQuited) {
        cv.notify_all();
    }
    if (requestExecutor.joinable())
        requestExecutor.join();
}

void ConnectExecutor::add_socket(std::shared_ptr<Item> item, Listener listener) {
    {
        std::lock_guard<std::mutex> l(mutex);
        requestQueue.push(std::make_pair(item, listener));
    }
    cv.notify_all();
}

void ConnectExecutor::add_socket_impl() {
#if linux
    while (!shouldQuit) {
        std::unique_lock<std::mutex> lock(mutex);
        while (requestQueue.size() || countNow != 0) {
            if (requestQueue.size() && countNow != size) {
                auto request = requestQueue.front();
                requestQueue.pop();
                mutex.unlock();
                std::shared_ptr<Item> item = request.first;
                send(item.get()->sock, item.get()->message, sizeof(item.get()->message), 0);
                epoll_event ev;
                ev.data.fd = item.get()->sock;
                ev.events = EPOLLIN;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, item.get()->sock, &ev) != -1) {
                    listeners.insert(std::make_pair(item.get()->sock, request.second));
                    results[item.get()->sock] = "";
                }
                countNow++;
                mutex.lock();
            }
            epoll_event events[size];
            int epoll_amount = epoll_wait(epoll_fd, events, size, 10);

            for (int i = 0; i < epoll_amount; i++) {
                const int BUFFER_SIZE = 100;
                if (events[i].events & EPOLLIN) {
                    int fd = events[i].data.fd;
                    char buf[BUFFER_SIZE];
                    memset(&buf[0], 0, sizeof(buf));
                    if (BUFFER_SIZE == 1) {
                        recv(fd, buf, sizeof(buf), 0);
                    } else {
                        recv(fd, buf, sizeof(buf) - sizeof(char), 0);
                    }
                    if (buf[0] != 0) {
                        results[fd] += buf;
                    } else {
                        close(fd);
                        std::stringstream ss(results[fd].c_str());
                        std::string to;
                        for (int j = 0; j < 5; j++)
                            std::getline(ss, to, '\n');
                        std::string result = "";
                        while (std::getline(ss, to, '\n')) {
                            result += to + "\n";
                        }
                        Listener listener = (*listeners.find(fd)).second;
                        listeners.erase(fd);
                        countNow--;
                        responseExecutor.enqueue_work([this, listener, result]() -> void {
                            listener.onSuccess(nlohmann::json::parse(result));
                        });
                    }
                }
            }
        }
        cv.notify_all();
        cv.wait(lock);
    }
    isQuited = true;
#elif __APPLE__
    while (!shouldQuit) {
        std::unique_lock<std::mutex> lock(mutex);
        while (requestQueue.size()) {
            auto request = requestQueue.front();
            std::shared_ptr<Item> item = request.first;
            requestQueue.pop();
            mutex.unlock();
            send(item.get()->sock, item.get()->message, sizeof(item.get()->message), 0);
            std::string result;

            char buf[1];
            do {
                buf[0] = 0;
                recv(item.get()->sock, buf, sizeof(buf), 0);
                if (buf[0] != 0)
                    result += buf[0];
            } while (buf[0] != 0);

            std::stringstream ss(result.c_str());
            std::string to;

            for (int i = 0; i < 5; i++)
                std::getline(ss, to, '\n');

            result = "";
            while (std::getline(ss, to, '\n')) {
                result += to + "\n";
            }

            nlohmann::json json_result = nlohmann::json::parse(result);
            Listener listener = request.second;
            responseExecutor.enqueue_work([this, listener, json_result]() -> void {
                Listener l = listener;
                l.onSuccess(json_result);
            });
            mutex.lock();
        }
        cv.notify_all();
        cv.wait(lock);
    }
    isQuited = true;
#endif
}

