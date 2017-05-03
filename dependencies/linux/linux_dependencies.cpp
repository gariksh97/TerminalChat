//
// Created by garik on 29.04.17.
//

#include "linux_dependencies.h"
#include <libnotify/notify.h>
#include <termios.h>
#include <iostream>

int notify(std::string name, std::string field) {
    notify_init("TerminalChat");
    NotifyNotification* n = notify_notification_new (name.c_str(),
                                                     field.c_str(),
                                                     0);
    notify_notification_set_timeout(n, 10000); // 10 seconds

    if (!notify_notification_show(n, 0))
    {
        std::cerr << "show has failed" << std::endl;
        return -1;
    }
    return 0;
}

void SetStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

std::string inputPassword() {

    SetStdinEcho(false);

    std::string password;
    std::cin >> password;

    SetStdinEcho(true);

    return password;
}


