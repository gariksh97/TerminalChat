//
// Created by garik on 04.05.17.
//

#ifndef TERMINALCHAT_CHATMODEL_H
#define TERMINALCHAT_CHATMODEL_H

#include <string>
#include <vector>
#include "MessageModel.h"


class ChatModel {
public:
    ChatModel(std::string name);
    ~ChatModel();

    ChatModel& operator=(ChatModel const& other);

    void setMessages(std::vector<MessageModel> messages);
    std::vector<MessageModel>& getMessages();

    std::string getName();

    void addMessage(MessageModel const& message);

    MessageModel getLastMessage();

private:
    std::string name;
    std::vector<MessageModel> messages;
};


#endif //TERMINALCHAT_CHATMODEL_H
