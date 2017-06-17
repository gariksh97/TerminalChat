//
// Created by garik on 27.04.17.
//

#ifndef TERMINALCHAT_NETWORKING_H
#define TERMINALCHAT_NETWORKING_H


#include "Listener.h"
#include "ThreadExecutor.h"
#include "../dependencies/ConnectExecutor.h"
#include <string>
#include <thread>
#include <condition_variable>

class Networking {
public:
    static Networking &getInstance(bool value = false) {
        static Networking instance(value);
        return instance;
    }
    static std::string encode(std::string s);
    static std::string decode(std::string s);


    void add_request(Listener listener, std::string url);

    ~Networking();

private:
    Networking(bool async);

    bool async;
    ConnectExecutor executor;

    void add_request_sync(Listener listener, std::string url);
    void add_request_async(Listener listener, std::string url);

    static const std::string HOST;
    static const std::string FULL_HOST;
    static const uint16_t PORT;
};


#endif //TERMINALCHAT_NETWORKING_H
