//
// Created by garik on 04.05.17.
//

#include "MessageModel.h"


MessageModel::MessageModel(std::string from, std::string message) {
    this->from = from;
    this->message = message;
}

MessageModel::~MessageModel() {}

MessageModel& MessageModel::operator=(MessageModel const &other) {
    this->from = other.from;
    this->message = other.message;
    return *this;
}

std::string MessageModel::getFrom() {
    return this->from;
}

std::string MessageModel::getMessage() {
    return this->message;
}