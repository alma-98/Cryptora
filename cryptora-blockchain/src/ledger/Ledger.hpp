#pragma once

#include "../transaction/Transaction.hpp"

#include <string>
#include <unordered_map>

namespace cryptora {

class Ledger {

private:

    std::unordered_map<std::string, long double>
        balances;

public:

    Ledger() = default;

    void applyTransaction(
            const Transaction& transaction
    ) {

        if (transaction.asset != "CRC") {
            return;
        }

        if (transaction.from.empty() ||
            transaction.to.empty()) {
            return;
        }

        const long double amount =
            std::stold(transaction.amount);

        if (amount <= 0) {
            return;
        }

        balances[transaction.from] -= amount;

        balances[transaction.to] += amount;
    }

    long double getBalance(
            const std::string& address
    ) const {

        const auto iterator =
            balances.find(address);

        if (iterator == balances.end()) {
            return 0;
        }

        return iterator->second;
    }
};

}
