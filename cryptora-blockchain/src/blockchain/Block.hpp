#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace cryptora {

struct Block {
    std::uint64_t height{};
    std::string previousHash;
    std::string hash;
    std::uint64_t timestamp{};
    std::vector<std::string> transactionIds;
};

}
