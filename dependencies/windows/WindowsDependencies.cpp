//
// Created by garik on 03.05.17.
//

#include "WindowsDependencies.h"
#include <windows.h>
#include <iostream>
#include <thread>


void notify(std::string name, std::string text) {
    //TODO: NEED TO CREATE NEW THREAD
    std::string value = "bin\\windows\\notify-send.exe \"" + name + "\" \"" + text + "\"";
    system(value.c_str());
};

std::string inputPassword() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    std::string s;
    getline(std::cin, s);
    return s;
};