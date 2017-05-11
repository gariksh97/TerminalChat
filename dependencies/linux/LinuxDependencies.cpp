//
// Created by garik on 29.04.17.
//

#include "LinuxDependencies.h"
#include "tui/ChatTUI.h"
#include <termios.h>
#include <iostream>
#include <fstream>
#include <zconf.h>


void SetStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

std::string inputPassword() {

    SetStdinEcho(false);

    std::string password;
    std::cin >> password;

    SetStdinEcho(true);

    return password;
}

void openTUI() {
    ChatTUI chatTUI;
    chatTUI.start();
}

void saveToken(std::string s) {
    std::ofstream token_file;
    token_file.open ("chat_token");
    token_file << s;
    token_file.close();
}

std::string loadToken() {
    std::string token;
    std::ifstream token_file;
    token_file.open("chat_token");
    token_file >> token;
    return token;
}

