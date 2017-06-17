//
// Created by garik on 27.05.17.
//

#ifndef TERMINALCHAT_CONNECTEXECUTOR_H
#define TERMINALCHAT_CONNECTEXECUTOR_H


#include <condition_variable>
#include <netinet/in.h>
#include <netdb.h>
#include "../network/ThreadExecutor.h"
#include "../network/Listener.h"

class ConnectExecutor {

public:
    class Item;
    ConnectExecutor(unsigned int count, unsigned int threadCount);
    ~ConnectExecutor();

    void add_socket(std::shared_ptr<Item> item, Listener listener);

private:


    void add_socket_impl();

#if linux
    int epoll_fd;
    int countNow;
    std::map<int, Listener> listeners;
    std::map<int, std::string> results;
#elif __APPLE__
#endif
    int size;

    volatile bool shouldQuit = false;
    volatile bool isQuited = false;

    std::condition_variable cv;
    std::mutex mutex;

    std::queue<std::pair<std::shared_ptr<Item>, Listener>> requestQueue;

    std::thread requestExecutor;
    ThreadExecutor responseExecutor;
};

class ConnectExecutor::Item {
public:
    int sock;
    sockaddr_in addr;
    hostent *raw_host;
    char message[1000];
};


#endif //TERMINALCHAT_CONNECTEXECUROT_H
