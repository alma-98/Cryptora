#pragma once

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace cryptora {

class HttpServer {

private:

    int port;
    int serverSocket{-1};

public:

    explicit HttpServer(int serverPort)
        : port(serverPort) {
    }

    ~HttpServer() {

        if (serverSocket >= 0) {
            close(serverSocket);
        }
    }

    int getPort() const {
        return port;
    }

    bool start(
            const std::function<std::string(
                const std::string&,
                const std::string&,
                const std::string&
            )>& handler
    ) {

        serverSocket =
            socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket < 0) {

            std::cerr
                << "Failed to create socket: "
                << std::strerror(errno)
                << std::endl;

            return false;
        }

        int option = 1;

        setsockopt(
            serverSocket,
            SOL_SOCKET,
            SO_REUSEADDR,
            &option,
            sizeof(option)
        );

        sockaddr_in address{};

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(
                serverSocket,
                reinterpret_cast<sockaddr*>(&address),
                sizeof(address)
            ) < 0) {

            std::cerr
                << "Failed to bind port "
                << port
                << ": "
                << std::strerror(errno)
                << std::endl;

            close(serverSocket);
            serverSocket = -1;

            return false;
        }

        if (listen(serverSocket, 16) < 0) {

            std::cerr
                << "Failed to listen: "
                << std::strerror(errno)
                << std::endl;

            close(serverSocket);
            serverSocket = -1;

            return false;
        }

        std::cout
            << "Cryptora Native Node listening on port "
            << port
            << std::endl;

        while (true) {

            sockaddr_in clientAddress{};
            socklen_t clientLength =
                sizeof(clientAddress);

            int clientSocket =
                accept(
                    serverSocket,
                    reinterpret_cast<sockaddr*>(
                        &clientAddress
                    ),
                    &clientLength
                );

            if (clientSocket < 0) {
                continue;
            }

            char buffer[16384]{};

            ssize_t received =
                recv(
                    clientSocket,
                    buffer,
                    sizeof(buffer) - 1,
                    0
                );

            if (received <= 0) {

                close(clientSocket);
                continue;
            }

            buffer[received] = '0';

            std::string request(buffer);

            std::string method;
            std::string path;
            std::string body;

            parseRequest(
                request,
                method,
                path,
                body
            );

            std::string responseBody =
                handler(method, path, body);

            sendResponse(
                clientSocket,
                responseBody
            );

            close(clientSocket);
        }

        return true;
    }

private:

    static void parseRequest(
            const std::string& request,
            std::string& method,
            std::string& path,
            std::string& body
    ) {

        const std::size_t firstSpace =
            request.find(' ');

        if (firstSpace == std::string::npos) {
            return;
        }

        method =
            request.substr(
                0,
                firstSpace
            );

        const std::size_t secondSpace =
            request.find(
                ' ',
                firstSpace + 1
            );

        if (secondSpace == std::string::npos) {
            return;
        }

        path =
            request.substr(
                firstSpace + 1,
                secondSpace - firstSpace - 1
            );

        const std::string separator =
            "\r\n\r\n";

        const std::size_t bodyPosition =
            request.find(separator);

        if (bodyPosition != std::string::npos) {

            body =
                request.substr(
                    bodyPosition + separator.length()
                );
        }
    }

    static void sendResponse(
            int clientSocket,
            const std::string& body
    ) {

        const std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " +
            std::to_string(body.size()) +
            "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            body;

        send(
            clientSocket,
            response.c_str(),
            response.size(),
            0
        );
    }
};

}
