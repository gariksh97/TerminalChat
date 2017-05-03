//
// Created by garik on 29.04.17.
//

#ifndef TERMINALCHAT_DEPENDENCIES_H
#define TERMINALCHAT_DEPENDENCIES_H

#include <string>



struct dependencies {
    static void notify(std::string name, std::string text);
    static std::string inputPassword();
};

#endif //TERMINALCHAT_DEPENDENCIES_H
