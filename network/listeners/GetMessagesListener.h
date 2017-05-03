//
// Created by garik on 03.05.17.
//

#ifndef TERMINALCHAT_GETMESSAGESLISTENER_H
#define TERMINALCHAT_GETMESSAGESLISTENER_H


#include "Listener.h"

class GetMessagesListener : public Listener {
protected:
    virtual void onSuccess(unsigned int status_code, std::string result) {};

    virtual void onError(std::exception& e) {
        Listener::onError(e);
    }
};


#endif //TERMINALCHAT_GETMESSAGESLISTENER_H
