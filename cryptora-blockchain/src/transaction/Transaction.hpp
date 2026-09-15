#pragma once

#include <string>

namespace cryptora {

struct Transaction {
    std::string id;
    std::string from;
    std::string to;
    std::string asset;
    std::string amount;
    std::string tenor;
    std::string status;
};

}
