//
// Created by garik on 04.05.17.
//

#include "ChatTUI.h"
#include "TUIHelper.h"
#include "../dependencies/DependenciesTUI.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

ChatTUI::ChatTUI() {
    state = CHATS;
    y = 0;
    x = 0;
}

ChatTUI::~ChatTUI() {}

void ChatTUI::start() {

    ChatModel chat("Alex Kolchanov");
    chat.addMessage(MessageModel("Garik", "Hello"));
    chat.addMessage(MessageModel("Alex", "Hi"));

    std::vector<ChatModel> chats;

    chats.push_back(ChatModel("Garik Shakhbazyan"));
    chats.push_back(ChatModel("Trofimov Ivan"));
    chats.push_back(ChatModel("Chat Room 1"));
    chats.push_back(ChatModel("Chat Room 1"));
    chats.push_back(ChatModel("Chat Room 1"));
    chats.push_back(ChatModel("Chat Room 1"));
    chats.push_back(chat);

    this->chatList.setChats(chats);
    this->chat.setChat(chats[1]);

     DependenciesTUI::tui_initscr();
    DependenciesTUI::tui_keypad();
    DependenciesTUI::tui_raw();
    DependenciesTUI::tui_noecho();
    DependenciesTUI::tui_nonl();
    bool shouldQuit = false;
    while (!shouldQuit) {
        int maxX = DependenciesTUI::tui_getmaxx();
        int maxY = DependenciesTUI::tui_getmaxy();
        int chatListX = min(20, maxX / 2);
        int chatListY = maxY - 2;
        int chatY = maxY - max(10, maxY / 3);
        DependenciesTUI::tui_clear();
        this->chatList.show(0, 0, chatListX, chatListY);
        this->chatList.setSelected();
        this->chat.show(
                chatListX + 2,
                0,
                maxX,
                chatY
        );
        this->textBox.show(
                chatListX + 2,
                chatY + 2,
                maxX,
                maxY - 2
        );
        TUIHelper::drawVerticalLine(
                chatListX + 1,
                0,
                maxY - 2
        );
        TUIHelper::drawHorizontalLine(
                chatListX + 2,
                maxX,
                chatY + 1
        );
        TUIHelper::drawHorizontalLine(0, maxX, maxY - 2);

        switch (state) {
            case CHATS:
                DependenciesTUI::tui_mvprintw(maxY - 1, 0,
                                              "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT | ENTER: SELECT CHAT"
                );
                break;
            case TEXT_BOX:
                DependenciesTUI::tui_mvprintw(maxY - 1, 0,
                                              "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT | ENTER: SEND MESSAGE"
                );
                break;
            case MESSAGES:
                DependenciesTUI::tui_mvprintw(maxY - 1, 0,
                                              "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT"
                );
                break;
            default:
                break;
        }
        DependenciesTUI::tui_move(y, x);
        DependenciesTUI::tui_refresh();
        int c = DependenciesTUI::tui_getch();
        switch (c) {
            case DependenciesTUI::TUI_F4:
                shouldQuit = true;
                break;
            case DependenciesTUI::TUI_F3:
                state = MESSAGES;
                break;
            case DependenciesTUI::TUI_F2:
                state = TEXT_BOX;
                break;
            case DependenciesTUI::TUI_F1:
                state = CHATS;;
                break;
            default:
                switch (state) {
                    case MESSAGES:
                        onMessages(c);
                        break;
                    case TEXT_BOX:
                        onTextBox(c);
                        break;
                    case CHATS:
                        onChatsList(c);
                        break;
                    default:
                        break;
                }
        }
        switch (state) {
            case CHATS:
                y = chatList.getY();
                x = chatList.getX();
                break;
            case TEXT_BOX:
                y = textBox.getY();
                x = textBox.getX();
                break;
            case MESSAGES:
                y = 0;
                x = chatListX + 2;
                break;
            default:
                break;
        }
    };
    exit();
}

void ChatTUI::exit() {
    DependenciesTUI::tui_clear();
    DependenciesTUI::tui_refresh();
    DependenciesTUI::tui_endwin();
}

void ChatTUI::onChatsList(int c) {
    if (c == DependenciesTUI::TUI_UP) {
        chatList.moveTo(ChatList::UP);
        return;
    }
    if (c == DependenciesTUI::TUI_DOWN) {
        chatList.moveTo(ChatList::DOWN);
        return;
    }
    if (c == DependenciesTUI::TUI_ENTER || c == '\n' || c == '\r') {
        chatList.setSelected();
        chat.setChat(chatList.getChat());
        return;
    }
}

void ChatTUI::onMessages(int c) {
    if (c == DependenciesTUI::TUI_UP) {
        chat.moveTo(Chat::UP);
        return;
    }
    if (c == DependenciesTUI::TUI_DOWN) {
        chat.moveTo(Chat::DOWN);
        return;
    }
}

void ChatTUI::onTextBox(int c) {

    if (c == DependenciesTUI::TUI_UP) {
        textBox.moveTo(TextBox::UP);
        return;
    }
    if (c == DependenciesTUI::TUI_DOWN) {
        textBox.moveTo(TextBox::DOWN);
        return;
    }
    if (c == DependenciesTUI::TUI_LEFT) {
        textBox.moveTo(TextBox::LEFT);
        return;
    }
    if (c == DependenciesTUI::TUI_RIGHT) {
        textBox.moveTo(TextBox::RIGHT);
        return;
    }
    if (c == DependenciesTUI::TUI_BACKSPACE) {
        textBox.removeCharacter();
        return;
    }
    if (c == DependenciesTUI::TUI_ENTER || c == '\n' || c == '\r') {
        sendMessage();
        return;
    }
    if (isprint(c)) {
        textBox.addCharacter(c);
        return;
    }
}

void ChatTUI::sendMessage() {
    chatList.getChat().addMessage(MessageModel("Garik", textBox.getText()));
    chat.setChat(chatList.getChat());
    textBox.clear();
}