//
// Created by garik on 27.04.17.
//

#ifndef TERMINALCHAT_LOGINLISTENER_H
#define TERMINALCHAT_LOGINLISTENER_H


#include "Listener.h"

class LoginListener : public Listener {
protected:
    virtual void onSuccess(unsigned int status_code, std::string result);

    virtual void onError(std::exception& e) {
        Listener::onError(e);
    }
};


#endif //TERMINALCHAT_LOGINLISTENER_H
