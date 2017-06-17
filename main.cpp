#include <iostream>
#include "network/Networking.h"
#include "dependencies/Dependencies.h"
#include "tui/ChatTUI.h"
#include <unistd.h>
#include "network/Errors.h"

void reg(int argv, char **args) {
    if (argv <= 3) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat register <login> <name>\"" << std::endl;
        return;
    }
    std::string login = args[2];
    std::string name = args[3];
    std::cout << "Enter password: ";
    std::string password = Dependencies::inputPassword();
    std::cout << std::endl;
    std::string request = "api/register";
    request += "/:login=" + Networking::encode(login);
    request += "/:password=" + Networking::encode(password);
    request += "/:name=" + Networking::encode(name);
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::REGISTER_ALREADY) {
                            std::cout << "User already registered. Use another login" << std::endl;
                        } else if (result_code == Errors::OK) {
                            std::cout << "Thanks for joining us. You're register" << std::endl;
                            Dependencies::saveToken(result["token"]);
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void login(int argv, char **args) {
    if (argv <= 2) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat login <login>\"" << std::endl;
        return;
    }
    std::string login = args[2];
    std::cout << "Enter password: ";
    std::string password = Dependencies::inputPassword();
    std::cout << std::endl;
    std::string request = "api/login";
    request += "/:login=" + Networking::encode(login);
    request += "/:password=" + Networking::encode(password);
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::OK) {
                            std::cout << "We wait you!" << std::endl;
                            Dependencies::saveToken(result["token"]);
                        } else if (result_code == Errors::INCORRECT_LOGIN_OR_PASSWORD) {
                            std::cout << "Incorrect login or password" << std::endl;
                        } else if (result_code == Errors::USER_NOT_EXIST) {
                            std::cout << "User not exists" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void create(int argv, char **args) {
    if (argv <= 1) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat create <name of room>\"" << std::endl;
        return;
    }
    std::string name = args[2];
    std::cout << "Enter password: [press Enter is no password]";
    std::string password = Dependencies::inputPassword();
    std::cout << std::endl;

    std::string request = "api/createRoom";
    request += "/:token=" + Dependencies::loadToken();
    request += "/:name=" + Networking::encode(name);
    request += "/:pw=" + Networking::encode(password);
    Networking::getInstance(false).add_request(
            Listener(
                    [name](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::OK) {
                            std::cout << "Room \"" + name + "\" is created" << std::endl;
                        } else if (result_code == Errors::WRONG_TOKEN) {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == Errors::ROOM_ALREADY_EXISTS) {
                            std::cout << "Room already exists" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void send(int argv, char **args) {
    if (argv <= 3) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat send <name of room> <message>\"" << std::endl;
        return;
    }
    std::string name = args[2];
    std::string message = args[3];

    std::string request = "api/sendMessage";
    request += "/:token=" + Dependencies::loadToken();
    request += "/:roomName=" + Networking::encode(name);
    request += "/:text=" + Networking::encode(message);
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::OK) {
                            std::cout << "Message sent";
                        } else if (result_code == Errors::WRONG_TOKEN) {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == Errors::ROOM_NOT_EXISTS) {
                            std::cout << "Room not exists" << std::endl;
                        } else if (result_code == Errors::ROOM_NOT_LOGIN) {
                            std::cout << "You not enter in this room" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void get(int argv, char **args) {
    if (argv <= 3) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat get <name of room> <count>\"" << std::endl;
        return;
    }
    std::string name = args[2];
    std::string amount = args[3];

    std::string request = "api/getTopMessage";
    request += "/:token=" + Dependencies::loadToken() + "";
    request += "/:roomName=" + Networking::encode(name) + "";
    request += "/:amount=" + Networking::encode(amount) + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::OK) {
                            nlohmann::json messages = result["messages:"];
                            for (int i = 0; i < messages.size(); i++) {
                                std::cout << Dependencies::getUserNameById(messages[i]["userId"]) << " (";
                                std::cout << Networking::decode(messages[i]["date"]) << "):" << std::endl;
                                std::cout << Networking::decode(messages[i]["text"]) << std::endl;
                            }
                        } else if (result_code == Errors::WRONG_TOKEN) {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == Errors::ROOM_NOT_EXISTS) {
                            std::cout << "Room not exists" << std::endl;
                        } else if (result_code == Errors::ROOM_NOT_LOGIN) {
                            std::cout << "You not enter in this room" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void join(int argv, char **args) {
    if (argv <= 2) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat join <name of room>\"" << std::endl;
        return;
    }
    std::string name = args[2];

    std::cout << "Enter password: ";
    std::string password = Dependencies::inputPassword();
    std::cout << std::endl;

    std::string request = "api/connectToRoom";
    request += "/:token=" + Dependencies::loadToken() + "";
    request += "/:roomName=" + Networking::encode(name) + "";
    request += "/:pw=" + Networking::encode(password) + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        int result_code = result["code"];
                        if (result_code == Errors::OK) {
                            std::cout << "You're connected to room" << std::endl;
                        } else if (result_code == Errors::WRONG_TOKEN) {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == Errors::ALREADY_IN_ROOM) {
                            std::cout << "You're already in this room" << std::endl;
                        } else if (result_code == Errors::INCORRECT_LOGIN_OR_PASSWORD) {
                            std::cout << "Wrong password" << std::endl;
                        } else if (result_code == Errors::ROOM_NOT_EXISTS) {
                            std::cout << "There isn't such room" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

void getUsers() {
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        Dependencies::saveUsers(result["users"]);
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            "api/getUsers"
    );
}

int main(int argv, char **args) {
    std::string request = argv != 1 ? args[1] : "";


    if (request == "tui") {
        Networking::getInstance(true).add_request(
                Listener(
                        [](nlohmann::json result) -> void {
                            Dependencies::saveUsers(result["users"]);
                        },
                        [](std::exception e) -> void {
                            exit(1);
                        }
                ),
                "api/getUsers"
        );
        Networking::getInstance(true).add_request(
                Listener(
                        [](nlohmann::json result) -> void {
                            Dependencies::saveRooms(result["rooms"]);
                        },
                        [](std::exception e) -> void {
                            exit(1);
                        }
                ),
                "api/getRooms"
        );
        ChatTUI chatTUI;
        if (argv >= 3) {
            chatTUI.setTimerSize(atoi(args[2]));
        }
        chatTUI.start();
    } else {

        if (request == "register") {
            reg(argv, args);
        } else if (request == "login") {
            login(argv, args);
        } else if (request == "send") {
            send(argv, args);
        } else if (request == "create") {
            create(argv, args);
        } else if (request == "join") {
            join(argv, args);
        } else if (request == "get") {
            getUsers();
            get(argv, args);
        } else {
            std::cout << "Use: " << std::endl;
            std::cout << "\tregister" << std::endl;
            std::cout << "\tlogin" << std::endl;
            std::cout << "\tsend" << std::endl;
            std::cout << "\tcreate" << std::endl;
            std::cout << "\tjoin" << std::endl;
            std::cout << "\ttui <update time = 10>" << std::endl;
        }
    }
}

