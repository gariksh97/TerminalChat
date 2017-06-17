//
// Created by garik on 27.04.17.
//

#include "Networking.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <curl/curl.h>
#include "../json/json.hpp"

const std::string Networking::HOST = "93.189.43.66";
const std::string Networking::FULL_HOST = "http://" + HOST;
const uint16_t Networking::PORT = 8080;


Networking::Networking(bool async) : executor(20, 2) {
    this->async = async;
}

Networking::~Networking() {
}

void Networking::add_request(Listener listener, std::string url) {
    if (async) {
        add_request_async(listener, url);
    } else {
        add_request_sync(listener, url);
    }
}

void Networking::add_request_sync(Listener listener, std::string url) {
    std::stringstream request;
    request << "GET " << FULL_HOST << "/" << url << " HTTP/1.0\r\n";
    request << "HOST: " << HOST << "\r\n";
    request << "Accept: */*\r\n";
    request << "Connection: close\r\n\r\n";

#ifdef DEBUG
    std::cout << message << std::endl;
#endif
    int sock;
    struct sockaddr_in addr;
    struct hostent *raw_host;
    raw_host = gethostbyname(HOST.c_str());
    if (raw_host == NULL) {
        std::cout << "ERROR, no such host";
        exit(0);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    bcopy(
            raw_host->h_addr,
            &addr.sin_addr,
            raw_host->h_length
    );
    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cerr << "connect error" << std::endl;
        exit(2);
    }

    char message[1000] = {};
    request.read(message, 1000);
    send(sock, message, sizeof(message), 0);
    std::string result;

    char buf[1];
    do {
        buf[0] = 0;
        recv(sock, buf, sizeof(buf), 0);
        if (buf[0] != 0)
            result += buf[0];
    } while (buf[0] != 0);

    std::stringstream ss(result.c_str());
    std::string to;

    for (int i = 0; i < 5; i++)
        std::getline(ss, to, '\n');

    result = "";
    while (std::getline(ss, to, '\n')) {
        result += to + "\n";
    }

    nlohmann::json json_result = nlohmann::json::parse(result);
    listener.onSuccess(json_result);
}


void Networking::add_request_async(Listener listener, std::string url) {
    std::stringstream request;
    request << "GET " << FULL_HOST << "/" << url << " HTTP/1.0\r\n";
    request << "HOST: " << HOST << "\r\n";
    request << "Accept: */*\r\n";
    request << "Connection: keep-alive\r\n\r\n";

#ifdef DEBUG
    std::cout << message << std::endl;
#endif
    std::shared_ptr<ConnectExecutor::Item> item(new ConnectExecutor::Item());
    item.get()->raw_host = gethostbyname(HOST.c_str());
    if (item.get()->raw_host == NULL) {
        std::cout << "ERROR, no such host";
        exit(0);
    }
    item.get()->sock = socket(AF_INET, SOCK_STREAM, 0);
    item.get()->addr.sin_family = AF_INET;
    item.get()->addr.sin_port = htons(PORT);
    bcopy(
            item.get()->raw_host->h_addr,
            &item.get()->addr.sin_addr,
            item.get()->raw_host->h_length
    );
    if (connect(item.get()->sock, (struct sockaddr *) &item.get()->addr, sizeof(item.get()->addr)) < 0) {
        std::cerr << "connect error" << std::endl;
        exit(2);
    }
    request.read(item.get()->message, 1000);
    executor.add_socket(item, listener);
}

std::string Networking::encode(std::string s) {
    CURL *curl = curl_easy_init();
    std::string result;
    if (curl) {
        char *output = curl_easy_escape(curl, s.c_str(), s.length());
        result = std::string(output);
        curl_free(output);
    }
    return result;
}

std::string Networking::decode(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+') s[i] = ' ';
    }
    CURL *curl = curl_easy_init();
    std::string result;
    if (curl) {
        char *output = curl_easy_unescape(curl, s.c_str(), s.length(), NULL);
        result = std::string(output);
        curl_free(output);
    }
    return result;
}




