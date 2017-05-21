//
// Created by garik on 29.04.17.
//

#include "Dependencies.h"
#include <iostream>


#if linux

#include <libnotify/notify.h>
#include <termio.h>
#include <fstream>

void SetStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

std::string Dependencies::inputPassword() {
    SetStdinEcho(false);

    std::string password;
    std::getline(std::cin, password);

    SetStdinEcho(true);
    return password;
}

void Dependencies::saveToken(std::string token) {
    std::ofstream token_file;
    token_file.open("chat_token");
    token_file << token;
    token_file.close();
}

std::string Dependencies::loadToken() {
    std::string token;
    std::ifstream token_file;
    token_file.open("chat_token");
    token_file >> token;
    return token;
}

void Dependencies::notify(std::string name, std::string text) {
    notify_init("TerminalChat");
    NotifyNotification *n = notify_notification_new(
            name.c_str(), text.c_str(), 0
    );
    notify_notification_set_timeout(n, 10000); // 10 seconds
    if (!notify_notification_show(n, 0)) {
        std::cerr << "show has failed" << std::endl;
        return;
    }
}

#elif _WIN32

#endif





