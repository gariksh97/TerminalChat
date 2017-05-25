//
// Created by garik on 29.04.17.
//

#ifndef TERMINALCHAT_DEPENDENCIES_H
#define TERMINALCHAT_DEPENDENCIES_H

#include <string>
#include <map>
#include "../json/json.hpp"


struct Dependencies {
private:
    static std::map<int, std::string> users;
    static std::map<int, std::string> rooms;
public:
    static std::string inputPassword();

    static void saveToken(std::string);
    static std::string loadToken();

    static void saveUsers(nlohmann::json result);
    static void saveRooms(nlohmann::json result);
    static std::string getUserNameById(int id);
    static std::string getRoomNameById(int id);

    static void notify(std::string name, std::string text);
};

#endif //TERMINALCHAT_DEPENDENCIES_H
