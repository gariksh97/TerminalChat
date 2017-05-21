//
// Created by garik on 17.05.17.
//

#ifndef TERMINALCHAT_ERRORS_H
#define TERMINALCHAT_ERRORS_H
#undef OK

class Errors {
public:
    static constexpr int OK =                              0;
    static constexpr int INCORRECT_LOGIN_OR_PASSWORD =     10;
    static constexpr int WRONG_TOKEN =                     30;
    static constexpr int REGISTER_ALREADY =                50;
    static constexpr int USER_NOT_EXIST =                  60;
    static constexpr int ROOM_NOT_EXISTS =                 80;
    static constexpr int ROOM_ALREADY_EXISTS =             90;
    static constexpr int ALREADY_IN_ROOM =                 100;
};

#endif //TERMINALCHAT_ERRORS_H
