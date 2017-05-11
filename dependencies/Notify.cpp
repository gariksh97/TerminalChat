//
// Created by garik on 11.05.17.
//

#include "Notify.h"

#if linux

#include "linux/LinuxDependencies.h"

#elif _WIN32

#include "windows/windows_dependencies.h"

#elif _APPLE
//
#endif

void Dependencies::notify(std::string name, std::string text) {
    ::notify(name, text);
}