#pragma once

#include "Hash.hpp"
#include "../transaction/Transaction.hpp"

#include <string>

namespace cryptora {

class TransactionHasher {

public:

    static std::string createId(
            const Transaction& transaction
    ) {

        const std::string payload =
            transaction.from + "|" +
            transaction.to + "|" +
            transaction.asset + "|" +
            transaction.amount + "|" +
            transaction.tenor;

        return Hash::sha256(payload);
    }
};

}
