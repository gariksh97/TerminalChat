//
// Created by garik on 03.05.17.
//

#ifndef TERMINALCHAT_REGISTERLISTENER_H
#define TERMINALCHAT_REGISTERLISTENER_H


#include "Listener.h"

class RegisterListener : public Listener {
protected:
    virtual void onSuccess(unsigned int status_code, std::string result) {};

    virtual void onError(std::exception& e) {
        Listener::onError(e);
    }
};


#endif //TERMINALCHAT_REGISTERLISTENER_H
