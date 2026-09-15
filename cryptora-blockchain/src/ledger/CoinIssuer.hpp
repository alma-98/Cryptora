#pragma once

#include "CoinState.hpp"

#include <string>

namespace cryptora {

class CoinIssuer {

private:

    CoinState state;

public:

    CoinIssuer() = default;

    bool initialize(
            const std::string& symbol,
            const std::string& name,
            long double totalSupply
    ) {

        if (symbol.empty() ||
            name.empty() ||
            totalSupply <= 0) {

            return false;
        }

        state.symbol = symbol;
        state.name = name;
        state.totalSupply = totalSupply;
        state.issuedSupply = 0;
        state.active = true;

        return true;
    }

    bool issue(
            long double amount
    ) {

        if (!state.active ||
            amount <= 0) {

            return false;
        }

        if (state.issuedSupply + amount >
            state.totalSupply) {

            return false;
        }

        state.issuedSupply += amount;

        return true;
    }

    const CoinState& getState() const {
        return state;
    }
};

}
