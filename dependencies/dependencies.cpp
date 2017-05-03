//
// Created by garik on 29.04.17.
//

#include "dependencies.h"

#if linux

#include "linux/linux_dependencies.h"

#elif _WIN32

#include "windows/windows_dependencies.h"

#elif _APPLE
//
#endif

void dependencies::notify(std::string name, std::string text) {
    ::notify(name, text);
}

std::string dependencies::inputPassword() {
    return ::inputPassword();
}