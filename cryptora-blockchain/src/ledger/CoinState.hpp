#pragma once

#include <string>

namespace cryptora {

struct CoinState {

    std::string symbol = "CRC";

    std::string name =
        "Cryptora Coin";

    long double totalSupply = 0;

    long double issuedSupply = 0;

    bool active = true;
};

}
