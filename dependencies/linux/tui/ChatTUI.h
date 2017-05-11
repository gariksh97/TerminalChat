//
// Created by garik on 04.05.17.
//

#ifndef TERMINALCHAT_CHATTUI_H
#define TERMINALCHAT_CHATTUI_H


#include "ChatList.h"
#include "Chat.h"
#include "TextBox.h"

class ChatTUI {
    static constexpr int TEXT_BOX = 0;
    static constexpr int CHATS = 1;
    static constexpr int MESSAGES = 2;
public:
    ChatTUI();
    ~ChatTUI();

    void start();
    void exit();
private:
    void onTextBox(int c);
    void onChatsList(int c);
    void onMessages(int c);

    void sendMessage();

    int state;
    int x, y;

    ChatList chatList;
    Chat chat;
    TextBox textBox;
};


#endif //TERMINALCHAT_CHATTUI_H
