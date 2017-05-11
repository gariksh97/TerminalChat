//
// Created by garik on 29.04.17.
//

#ifndef TERMINALCHAT_LINUX_DEPENDENCIES_H
#define TERMINALCHAT_LINUX_DEPENDENCIES_H

#include <string>


std::string inputPassword();

void openTUI();

void saveToken(std::string s);

std::string loadToken();
#endif //TERMINALCHAT_LINUX_DEPENDENCIES_H
