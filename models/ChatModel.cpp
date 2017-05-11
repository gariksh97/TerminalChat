//
// Created by garik on 04.05.17.
//

#include "ChatModel.h"

ChatModel::ChatModel(std::string name) {
    this->name = name;
}

ChatModel::~ChatModel() {}

ChatModel &ChatModel::operator=(ChatModel const &other) {
    this->name = other.name;
    this->messages = other.messages;
    return *this;
}

void ChatModel::setMessages(std::vector<MessageModel> messages) {
    this->messages = messages;
}

void ChatModel::addMessage(MessageModel const &message) {
    this->messages.push_back(message);
}

std::vector<MessageModel>& ChatModel::getMessages() {
    return this->messages;
}

MessageModel ChatModel::getLastMessage() {
    //if (this->messages.size() == 0)
    //    return NULL;
    return this->messages[this->messages.size() - 1];
}

std::string ChatModel::getName() {
    return this->name;
}