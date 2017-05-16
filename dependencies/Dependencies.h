//
// Created by garik on 29.04.17.
//

#ifndef TERMINALCHAT_DEPENDENCIES_H
#define TERMINALCHAT_DEPENDENCIES_H

#include <string>




struct Dependencies {
    static std::string inputPassword();

    static void saveToken(std::string);
    static std::string loadToken();

    static void notify(std::string name, std::string text);

};

#endif //TERMINALCHAT_DEPENDENCIES_H
