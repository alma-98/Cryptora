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

    bool issue(
            const std::string& address,
            long double amount
    ) {

        if (address.empty() ||
            amount <= 0) {

            return false;
        }

        balances[address] += amount;

        return true;
    }

    bool applyTransaction(
            const Transaction& transaction
    ) {

        if (transaction.asset != "CRC") {
            return false;
        }

        if (transaction.from.empty() ||
            transaction.to.empty()) {

            return false;
        }

        long double amount;

        try {

            amount =
                std::stold(transaction.amount);

        } catch (...) {

            return false;
        }

        if (amount <= 0) {
            return false;
        }

        const auto sender =
            balances.find(transaction.from);

        if (sender == balances.end() ||
            sender->second < amount) {

            return false;
        }

        sender->second -= amount;

        balances[transaction.to] += amount;

        return true;
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
