//
// Created by garik on 29.04.17.
//

#include "Dependencies.h"
#include <iostream>
#include <map>

#ifdef linux
#include <libnotify/notify.h>

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

#endif


#if linux || __APPLE__

#include <termio.h>
#include <unistd.h>
#include <fstream>


std::map<int, std::string> Dependencies::users;
std::map<int, std::string> Dependencies::rooms;

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



void Dependencies::saveUsers(nlohmann::json result) {
    for (int i = 0; i < result.size(); i++) {
        int userId = result[i]["userId"];
        std::string name = result[i]["name"];
        users[userId] = name;
    }
}

void Dependencies::saveRooms(nlohmann::json result) {
    for (int i = 0; i < result.size(); i++) {
        int roomId = result[i]["roomId"];
        std::string name = result[i]["name"];
        rooms[roomId] = name;
    }
}

std::string Dependencies::getNameById(int id) {
    return Dependencies::users[id];
}

std::string Dependencies::getRoomNameById(int id){
    return Dependencies::rooms[id];
}

#elif _WIN32

#endif





