//
// Created by garik on 07.05.17.
//

#include "ThreadExecutor.h"
#include <chrono>
#include <thread>

ThreadExecutor::ThreadExecutor(unsigned int count) {
    executors.resize(count);
    for (int i = 0; i < count; i++) {
        executors[i] = std::thread(
                [this]() -> void { executor(); }
        );
    }
}

ThreadExecutor::~ThreadExecutor() {
    {
        std::lock_guard<std::mutex> l(mutex);
        shouldQuit = true;
    }
    while (isQuited != executors.size()) {
        cv.notify_all();
    }
    for (int i = 0; i < executors.size(); i++) {
        if (executors[i].joinable())
            executors[i].join();
    }
}

void ThreadExecutor::executor() {
    while (!shouldQuit) {
        std::unique_lock<std::mutex> lock(mutex);
        while (taskQueue.size()) {
            auto item = taskQueue.front();
            taskQueue.pop();
            mutex.unlock();
            item();
            mutex.lock();
        }
        cv.notify_all();
        cv.wait(lock);
    }
    isQuited++;
}

void ThreadExecutor::enqueueWork(std::function<void()> item) {
    {
        std::lock_guard<std::mutex> l(mutex);
        taskQueue.push(item);
    }
    cv.notify_all();
}
