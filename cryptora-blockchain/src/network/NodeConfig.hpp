#pragma once

#include <cstdint>
#include <string>

namespace cryptora {

struct NodeConfig {

    static constexpr std::uint16_t RPC_PORT = 8545;

    static constexpr const char* NETWORK =
        "cryptora-native";

    static constexpr const char* NATIVE_ASSET =
        "CRC";

    static constexpr const char* VERSION =
        "1.0.0";
};

}
