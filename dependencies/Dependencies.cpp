//
// Created by garik on 29.04.17.
//

#include "Dependencies.h"

#if linux

#include "linux/LinuxDependencies.h"

#elif _WIN32

#include "windows/windows_dependencies.h"

#elif _APPLE

#include "linux/LinuxDependencies.h"

#endif



std::string Dependencies::inputPassword() {
    return ::inputPassword();
}

void Dependencies::openTUI() {
    ::openTUI();
}

void Dependencies::saveToken(std::string token){
    ::saveToken(token);
}

std::string Dependencies::loadToken(){
    return ::loadToken();
}
