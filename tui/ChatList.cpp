//
// Created by garik on 04.05.17.
//

#include "ChatList.h"
#include "../dependencies/DependenciesTUI.h"

ChatList::ChatList() {
    pos = 0;
    selected = 0;
    offset = 0;
}

ChatList::~ChatList() {}

void ChatList::setChats(std::vector<ChatModel> chats) {
    this->chats = chats;
}

void ChatList::show(int fx, int fy, int tx, int ty) {
    if (y < fy || y > ty) {
        y = fy;
    }
    this->fy = fy;
    this->ty = ty;
    this->x = fx;
    if (pos / ITEM_SIZE + fy > ty) {
        pos = 0;
        y = fy;
    }
    for (size_t i = offset; i < chats.size() && fy <= ty; i++) {
        std::string name = chats[i].getName().c_str();
        if (tx - fx < name.length()) {
            name = name.substr(0, tx - fx);
        }
        DependenciesTUI::tui_mvprintw(fy, fx, name);
        fy += ITEM_SIZE;
    }
}

void ChatList::moveTo(int direction) {
    switch (direction) {
        case UP:
            if (pos > 0) {
                pos--;
                y -= ITEM_SIZE;
            }
            if (y < fy) {
                offset--;
                y += 2;
            }
            break;
        case DOWN:
            if (pos + 1 < chats.size()) {
                pos++;
                y += ITEM_SIZE;
            }
            if (y > ty) {
                y -= ITEM_SIZE;
                offset++;
            }
            break;
        default:
            break;
    }
}

int ChatList::getX() {
    return x;
}

int ChatList::getY() {
    return y;
}

void ChatList::setSelected() {
    this->selected = pos;
}

ChatModel& ChatList::getChat(){
    return chats[selected];
}