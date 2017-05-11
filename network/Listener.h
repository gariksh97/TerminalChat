//
// Created by garik on 27.04.17.
//

#include <string>
#include <iostream>
#include <functional>
#include "../json/json.hpp"

#ifndef TERMINALCHAT_LISTENER_H
#define TERMINALCHAT_LISTENER_H


class Listener {
public:
    typedef std::function<void(nlohmann::json)> onSuccessType;
    typedef std::function<void(std::exception)> onErrorType;

    Listener(onSuccessType onSuccessFunction, onErrorType onErrorFunction);

    Listener(Listener const &other);

    Listener &operator=(Listener const &other);

    ~Listener();

    void onSuccess(nlohmann::json result);

    void onError(std::exception e);

private:
    onSuccessType onSuccessFunction;
    onErrorType onErrorFunction;
};


#endif //TERMINALCHAT_LISTENER_H
