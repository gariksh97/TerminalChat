//
// Created by garik on 04.05.17.
//

#ifndef TERMINALCHAT_CHATLIST_H
#define TERMINALCHAT_CHATLIST_H


#include <vector>
#include "../models/ChatModel.h"

class ChatList {
public:
    static constexpr int UP = 0;
    static constexpr int DOWN = 1;


    ChatList();

    ~ChatList();

    void show(int fx, int fy, int tx, int ty);

    void moveTo(int direction);

    int getX();
    int getY();
    ChatModel& getChat();

    void setSelected();

    void setChats(std::vector<ChatModel> chats);

    bool isSelected();

private:
    static constexpr int ITEM_SIZE = 2;

    std::vector<ChatModel> chats;
    size_t offset;
    int fy, ty;
    int x, y;
    int pos;
    int selected;
};


#endif //TERMINALCHAT_CHATLIST_H
