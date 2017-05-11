//
// Created by garik on 04.05.17.
//

#ifndef TERMINALCHAT_MESSAGEMODEL_H
#define TERMINALCHAT_MESSAGEMODEL_H

#include <string>

class MessageModel {
public:
    MessageModel(std::string from, std::string message);
    ~MessageModel();

    MessageModel& operator=(MessageModel const& other);

    std::string getFrom();

    std::string getMessage();

private:
    std::string from;
    std::string message;
};


#endif //TERMINALCHAT_MESSAGEMODEL_H
