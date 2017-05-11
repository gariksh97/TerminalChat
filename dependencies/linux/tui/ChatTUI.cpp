//
// Created by garik on 04.05.17.
//

#include "ChatTUI.h"
#include "TUIHelper.h"
#include <ncurses.h>

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

    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    nonl();
    bool shouldQuit = false;
    while (!shouldQuit) {
        int maxX = getmaxx(stdscr);
        int maxY = getmaxy(stdscr);
        int chatListX = min(20, maxX / 2);
        int chatListY = maxY - 2;
        int chatY = maxY - max(10, maxY / 3);
        clear();
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
                mvprintw(maxY - 1, 0,
                         "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT | ENTER: SELECT CHAT"
                );
                break;
            case TEXT_BOX:
                mvprintw(maxY - 1, 0,
                         "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT | ENTER: SEND MESSAGE"
                );
                break;
            case MESSAGES:
                mvprintw(maxY - 1, 0,
                         "F1: CHATS | F2: TEXT BOX | F3 : MESSAGES | F4 : QUIT"
                );
                break;
            default:
                break;
        }
        move(y, x);
        refresh();
        int c = getch();
        switch (c) {
            case KEY_F(4):
                shouldQuit = true;
                break;
            case KEY_F(3):
                state = MESSAGES;
                break;
            case KEY_F(2):
                state = TEXT_BOX;
                break;
            case KEY_F(1):
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
    clear();
    refresh();
    endwin();
}

void ChatTUI::onChatsList(int c) {
    if (c == KEY_UP) {
        chatList.moveTo(ChatList::UP);
        return;
    }
    if (c == KEY_DOWN) {
        chatList.moveTo(ChatList::DOWN);
        return;
    }
    if (c == KEY_ENTER || c == '\n' || c == '\r') {
        chatList.setSelected();
        chat.setChat(chatList.getChat());
        return;
    }
}

void ChatTUI::onMessages(int c) {
    if (c == KEY_UP) {
        chat.moveTo(Chat::UP);
        return;
    }
    if (c == KEY_DOWN) {
        chat.moveTo(Chat::DOWN);
        return;
    }
}

void ChatTUI::onTextBox(int c) {

    if (c == KEY_UP) {
        textBox.moveTo(TextBox::UP);
        return;
    }
    if (c == KEY_DOWN) {
        textBox.moveTo(TextBox::DOWN);
        return;
    }
    if (c == KEY_LEFT) {
        textBox.moveTo(TextBox::LEFT);
        return;
    }
    if (c == KEY_RIGHT) {
        textBox.moveTo(TextBox::RIGHT);
        return;
    }
    if (c == KEY_BACKSPACE) {
        textBox.removeCharacter();
        return;
    }
    if (c == KEY_ENTER || c == '\n' || c == '\r') {
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