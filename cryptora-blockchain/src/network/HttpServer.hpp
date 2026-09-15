#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace cryptora {

class HttpServer {

private:

    int port;

public:

    explicit HttpServer(int serverPort)
        : port(serverPort) {
    }

    int getPort() const {
        return port;
    }

    void start(
            const std::function<void()>& callback
    ) const {

        std::cout
            << "Cryptora Native Node"
            << std::endl;

        std::cout
            << "Network: cryptora-native"
            << std::endl;

        std::cout
            << "RPC Port: "
            << port
            << std::endl;

        if (callback) {
            callback();
        }
    }
};

}
