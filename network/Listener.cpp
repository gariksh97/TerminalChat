//
// Created by garik on 07.05.17.
//

#include "../json/json.hpp"
#include "Listener.h"

Listener::Listener(onSuccessType onSuccessFunc, onErrorType onErrorFunc) {
    this->onSuccessFunction = onSuccessFunc;
    this->onErrorFunction = onErrorFunc;
}

Listener &Listener::operator=(Listener const &other) {
    this->onSuccessFunction = other.onSuccessFunction;
    this->onErrorFunction = other.onErrorFunction;
    return *this;
}

Listener::Listener(Listener const &other) {
    this->onSuccessFunction = other.onSuccessFunction;
    this->onErrorFunction = other.onErrorFunction;
}

Listener::~Listener() {

}

void Listener::onSuccess(nlohmann::json result) {
    onSuccessFunction(result);
}

void Listener::onError(std::exception e) {
    onErrorFunction(e);
}

