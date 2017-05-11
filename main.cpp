#include <iostream>
#include "network/Networking.h"
#include "dependencies/Dependencies.h"

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
    request += "/:login=" + login + "";
    request += "/:password=" + password + "";
    request += "/:name=" + name + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "50") {
                            std::cout << "User already registered. Use another login" << std::endl;
                        } else {
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
    request += "/:login=" + login + "";
    request += "/:password=" + password + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "0") {
                            std::cout << "We wait you!" << std::endl;
                            Dependencies::saveToken(result["token"]);
                        } else if (result_code == "10") {
                            std::cout << "Incorrect login or password" << std::endl;
                        } else if (result_code == "60") {
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
    request += "/:token" + Dependencies::loadToken() + "";
    request += "/:name=" + name + "";
    request += "/:pw=" + password + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [name](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "0") {
                            std::cout << "Room \"" + name + "\" is created";
                        } else if (result_code == "30") {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == "90") {
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
    request += "/:token" + Dependencies::loadToken() + "";
    request += "/:roomName=" + name + "";
    request += "/:text=" + message + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "0") {
                            std::cout << "Message sent";
                        } else if (result_code == "30") {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == "80") {
                            std::cout << "Room not exists" << std::endl;
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
        std::cout << "use \"chat send <name of room> <message>\"" << std::endl;
        return;
    }
    std::string name = args[2];
    std::string message = args[3];

    std::string request = "api/getMessage";
    request += "/:token" + Dependencies::loadToken() + "";
    request += "/:roomName=" + name + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "0") {
                            std::cout << "Message sent";
                        } else if (result_code == "30") {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == "80") {
                            std::cout << "Room not exists" << std::endl;
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
    if (argv <= 3) {
        std::cout << "Not enough arguments" << std::endl;
        std::cout << "use \"chat send <name of room> <message>\"" << std::endl;
        return;
    }
    std::string name = args[2];
    std::string message = args[3];

    std::string request = "api/sendMessage";
    request += "/:token" + Dependencies::loadToken() + "";
    request += "/:roomName=" + name + "";
    request += "/:text=" + message + "";
    Networking::getInstance(false).add_request(
            Listener(
                    [](nlohmann::json result) -> void {
                        std::string result_code = result["code"];
                        if (result_code == "0") {
                            std::cout << "Message sent";
                        } else if (result_code == "30") {
                            std::cout << "Please register or login again" << std::endl;
                        } else if (result_code == "80") {
                            std::cout << "Room not exists" << std::endl;
                        }
                    },
                    [](std::exception e) -> void {
                        std::cout << "Exception:" << e.what() << std::endl;
                    }
            ),
            request
    );
}

int main(int argv, char **args) {
    if (argv == 1) {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }
    std::string request = args[1];
    if (request == "tui") {
        Networking::getInstance(true);
        Dependencies::openTUI();
    } else if (request == "register") {
        reg(argv, args);
    } else if (request == "login") {
        login(argv, args);
    } else if (request == "send") {
        send(argv, args);
    } else if (request == "create") {
        create(argv, args);
    } else if (request == "join") {

    } else if (request == "get") {
        get(argv, args);
    } else {
        std::cout << "There is no such command" << std::endl;
        std::cout << "Use: " << std::endl;
        std::cout << "\tregister" << std::endl;
        std::cout << "\tlogin" << std::endl;
        std::cout << "\tsend" << std::endl;
        std::cout << "\tcreate" << std::endl;
    }
}

