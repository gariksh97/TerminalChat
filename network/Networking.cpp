//
// Created by garik on 27.04.17.
//

#include "Networking.h"
#include "boost/asio.hpp"
#include <iostream>
#include <glib.h>

Networking::Networking() {}

Networking::~Networking() {}

std::string Networking::encode(std::string url) {
    char *escape_char_str = (char *) "!*'();:@&=+$,/?#[]";
    char *encoded_uri = NULL;
    encoded_uri = g_uri_escape_string(url.c_str(), escape_char_str, TRUE);
    std::string result = encoded_uri;
    free(encoded_uri);
    return result;
}

void Networking::add_request(Listener &listener, std::string url) {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(HOST, "http");
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << "http://" + HOST + "/" + url << " HTTP/1.0\r\n";
        request_stream << "Host: " << encode(HOST) << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        boost::asio::write(socket, request);

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            return;
        }
        std::cout << "Response returned with status code " << status_code << "\n";

        /*Get result*/
        boost::asio::read_until(socket, response, "\r\n\r\n");
        std::string result;
        if (response.size() > 0) {
            std::ostringstream ss;
            ss << &response;
            result = ss.str();
        }
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
            std::ostringstream ss;
            ss << &response;
            result += ss.str();
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
        listener.onSuccess(status_code, result);
    } catch (std::exception e) {
        listener.onError(e);
    }
}
