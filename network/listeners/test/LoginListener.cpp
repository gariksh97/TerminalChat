//
// Created by garik on 27.04.17.
//

#include "../LoginListener.h"
#include <iostream>

void LoginListener::onSuccess(unsigned int status_code, std::string result) {
    std::cout << "Responce result:" << std::endl << result << std::endl;
}