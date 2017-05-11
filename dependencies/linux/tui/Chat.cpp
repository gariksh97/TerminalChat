//
// Created by garik on 07.05.17.
//

#include <ncurses.h>
#include "Chat.h"
#include "TUIHelper.h"

Chat::Chat() : chatModel("empty") {

}

Chat::~Chat() {

}

void Chat::setChat(ChatModel const &model) {
    this->chatModel = model;
    this->offset = 0;
}

void Chat::show(int fx, int fy, int tx, int ty) {
    if (chatModel.getMessages().size() == 0) return;
    for (int i = chatModel.getMessages().size() - 1 - offset; i >= 0 && fy <= ty; i--) {
        std::string message = chatModel.getMessages()[i].getMessage();
        while (tx - fx < message.length()) {
            mvprintw(ty--, fx, message.substr(0, tx - fx).c_str());
            message = message.substr(0, tx - fx);
        }
        if (message.length() != 0)
            mvprintw(ty--, fx, message.c_str());

        std::string from = chatModel.getMessages()[i].getFrom() + ":";
        while (tx - fx < from.length()) {
            mvprintw(ty--, fx, from.substr(0, tx - fx).c_str());
            from = from.substr(tx - fx, from.length());
        }
        if (from.length() != 0)
            mvprintw(ty--, fx, from.c_str());

        TUIHelper::drawHorizontalLine(fx, tx, ty--);
    }
}

void Chat::moveTo(int direction) {
    switch (direction) {
        case UP:
            if (chatModel.getMessages().size() != offset + 1)
                offset++;
            break;
        case DOWN:
            if (offset != 0)
                offset--;
            break;
    }
}
