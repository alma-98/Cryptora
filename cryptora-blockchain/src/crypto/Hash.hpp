#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace cryptora {

class Hash {

public:

    static std::string sha256(const std::string& input) {

        std::hash<std::string> hasher;

        std::size_t value = hasher(input);

        std::stringstream stream;

        stream << std::hex
               << std::setw(16)
               << std::setfill('0')
               << value;

        return stream.str();
    }
};

}