//
// Created by garik on 03.05.17.
//

#ifndef TERMINALCHAT_SENDMESSAGE_H
#define TERMINALCHAT_SENDMESSAGE_H


#include "Listener.h"

class SendMessageListener : public Listener {
protected:
    virtual void onSuccess(unsigned int status_code, std::string result) {};

    virtual void onError(std::exception& e) {
        Listener::onError(e);
    }
};


#endif //TERMINALCHAT_SENDMESSAGE_H
