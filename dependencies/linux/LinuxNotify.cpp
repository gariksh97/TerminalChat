//
// Created by garik on 11.05.17.
//

#include "LinuxNotify.h"
#include <libnotify/notify.h>
#include <iostream>

int notify(std::string name, std::string field) {
    notify_init("TerminalChat");
    NotifyNotification *n = notify_notification_new(name.c_str(),
                                                    field.c_str(),
                                                    0);
    notify_notification_set_timeout(n, 10000); // 10 seconds

    if (!notify_notification_show(n, 0)) {
        std::cerr << "show has failed" << std::endl;
        return -1;
    }
    return 0;
}