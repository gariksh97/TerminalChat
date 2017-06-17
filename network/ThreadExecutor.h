//
// Created by garik on 07.05.17.
//

#ifndef TERMINALCHAT_THREAD_EXECUTOR_H
#define TERMINALCHAT_THREAD_EXECUTOR_H

#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <queue>
#include <condition_variable>

class ThreadExecutor {
public:

    ThreadExecutor(unsigned int count);

    ~ThreadExecutor();

    void enqueue_work(std::function<void()> item);

private:
    void executor();

    volatile bool shouldQuit = false;
    volatile int isQuited = 0;
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::function<void()> > taskQueue;
    std::vector<std::thread> executors;
};


#endif //TERMINALCHAT_THREAD_EXECUTOR_H
