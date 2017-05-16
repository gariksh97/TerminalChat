//
// Created by garik on 27.04.17.
//

#include "Networking.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../json/json.hpp"

const std::string Networking::FULL_HOST = "http://93.189.43.66";
const std::string Networking::HOST = "93.189.43.66";
const uint16_t Networking::PORT = 8080;


Networking::Networking(bool async) : threadExecutor(1) {
    this->async = async;
}

Networking::~Networking() {
}

/*
std::string Networking::encode(std::string url) {
    char *escape_char_str = (char *) "!*'();:@&=+$,/?#[]";
    char *encoded_uri = NULL;
    encoded_uri = g_uri_escape_string(url.c_str(), escape_char_str, TRUE);
    std::string result = encoded_uri;
    free(encoded_uri);
    return result;
}
*/

void Networking::add_request(Listener listener, std::string url) {

    std::function<void()> function = [this, listener, url]() -> void {
        add_request_impl(
                listener, "v2/5185415ba171ea3a00704eed"
        );
    };
    if (async) {
        threadExecutor.enqueueWork(function);
    } else {
        add_request_impl(listener, url);
    }
}

void Networking::add_request_impl(Listener listener, std::string url) {
    std::stringstream request;
    request << "GET " << FULL_HOST << "/" << url << " HTTP/1.0\r\n";
    request << "HOST: " << HOST << "\r\n";
    request << "Accept: */*\r\n";
    request << "Connection: close\r\n\r\n";
    char message[1000] = {};
    request.read(message, 1000);
#ifdef SO_DEBUG
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
    send(sock, message, sizeof(message), 0);

    std::string result;

    char buf[1];
    do {
        buf[0] = NULL;
        recv(sock, buf, sizeof(buf), 0);
        if (buf[0] != NULL)
            result += buf[0];
    } while (buf[0] != NULL);

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




