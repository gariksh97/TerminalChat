//
// Created by garik on 07.05.17.
//

#include "Chat.h"
#include "TUIHelper.h"
#include "../dependencies/DependenciesTUI.h"

Chat::Chat() : chatModel("empty") {

}

Chat::~Chat() {

}

void Chat::setChat(ChatModel const &model) {
    this->chatModel = model;
    this->offset = 0;
}

void printText(int& fx, int& fy, int& tx, int& ty, std::string value) {
    int len = tx - fx;
    int ost = value.length() % len;
    DependenciesTUI::tui_mvprintw(ty--, fx, value.substr(value.length() - ost, value.length()));
    value = value.substr(0, value.length() - ost);
    while (value.length() != 0) {
        DependenciesTUI::tui_mvprintw(ty--, fx, value.substr(value.length() - len, value.length()));
        value = value.substr(0, value.length() - len);
    }
}

void Chat::show(int fx, int fy, int tx, int ty) {
    if (chatModel.getMessages().size() == 0) return;
    if (tx == fx) return;
    for (int i = chatModel.getMessages().size() - 1 - offset; i >= 0 && fy <= ty; i--) {
        std::string message = chatModel.getMessages()[i].getMessage();
        std::string from = chatModel.getMessages()[i].getFrom() + ":";
        printText(fx, fy, tx, ty, message);
        printText(fx, fy, tx, ty, from);

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
