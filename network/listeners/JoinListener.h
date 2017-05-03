//
// Created by garik on 03.05.17.
//

#ifndef TERMINALCHAT_JOINLISTENER_H
#define TERMINALCHAT_JOINLISTENER_H


#include "Listener.h"

class JoinListener : public Listener {
protected:
    virtual void onSuccess(unsigned int status_code, std::string result) {};

    virtual void onError(std::exception& e) {
        Listener::onError(e);
    }
};


#endif //TERMINALCHAT_JOINLISTENER_H
