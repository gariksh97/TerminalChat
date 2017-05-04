//
// Created by garik on 03.05.17.
//

#include "windows_dependencies.h"
#include <windows.h>

void notify(std::string name, std::string text) {
    std::string value = "bin\\windows\\notify-send.exe \"" + name + "\" \"" + text + "\"";
    system(value.c_str());
};

std::string inputPassword() {
    return "null";
};