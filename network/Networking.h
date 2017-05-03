//
// Created by garik on 27.04.17.
//

#ifndef TERMINALCHAT_NETWORKING_H
#define TERMINALCHAT_NETWORKING_H


#include "listeners/Listener.h"
#include <string>

class Networking {
public:
    static Networking &getInstance() {
        static Networking instance;
        return instance;
    }
    static std::string encode(std::string s);

    Networking();

    void add_request(Listener& listener, std::string url);

    ~Networking();

private:
    const std::string HOST = "www.mocky.io";
};


#endif //TERMINALCHAT_NETWORKING_H
