//
// Created by garik on 29.04.17.
//

#ifndef TERMINALCHAT_DEPENDENCIES_H
#define TERMINALCHAT_DEPENDENCIES_H

#include <string>



struct Dependencies {
    static std::string inputPassword();
    static void openTUI();

    static void saveToken(std::string);
    static std::string loadToken();
};

#endif //TERMINALCHAT_DEPENDENCIES_H
