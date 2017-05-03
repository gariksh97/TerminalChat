//
// Created by garik on 27.04.17.
//

#include <string>
#include <iostream>

#ifndef TERMINALCHAT_LISTENER_H
#define TERMINALCHAT_LISTENER_H


class Listener {
public:
    virtual void onSuccess(unsigned int status_code, std::string result) {

    };

    virtual void onError(std::exception& e) {
        std::cout << "No internet connection" << std::endl;
    };
};


#endif //TERMINALCHAT_LISTENER_H
