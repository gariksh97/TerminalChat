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

void Chat::show(int fx, int fy, int tx, int ty) {
    if (chatModel.getMessages().size() == 0) return;
    for (int i = chatModel.getMessages().size() - 1 - offset; i >= 0 && fy <= ty; i--) {
        std::string message = chatModel.getMessages()[i].getMessage();
        while (tx - fx < message.length()) {
            DependenciesTUI::tui_mvprintw(ty--, fx, message.substr(0, tx - fx));
            message = message.substr(0, tx - fx);
        }
        if (message.length() != 0)
            DependenciesTUI::tui_mvprintw(ty--, fx, message);

        std::string from = chatModel.getMessages()[i].getFrom() + ":";
        while (tx - fx < from.length()) {
            DependenciesTUI::tui_mvprintw(ty--, fx, from.substr(0, tx - fx));
            from = from.substr(tx - fx, from.length());
        }
        if (from.length() != 0)
            DependenciesTUI::tui_mvprintw(ty--, fx, from);

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
