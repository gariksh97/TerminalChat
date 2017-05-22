//
// Created by garik on 07.05.17.
//

#ifndef TERMINALCHAT_CHAT_H
#define TERMINALCHAT_CHAT_H


#include "../models/ChatModel.h"

class Chat {
public:
    static constexpr int UP = 0;
    static constexpr int DOWN = 1;

    Chat();
    ~Chat();

    void setChat(ChatModel const& model);
    void show(int fx, int fy, int tx, int ty);

    void moveTo(int direction);

private:

    ChatModel chatModel;
    int offset;
};


#endif //TERMINALCHAT_CHAT_H
