#pragma once

#include "Blockchain.hpp"
#include "../crypto/TransactionHasher.hpp"
#include "../transaction/Transaction.hpp"

#include <cstdint>
#include <string>

namespace cryptora {

class BlockchainService {

private:

    Blockchain blockchain;
    std::uint64_t transactionCounter{0};

public:

    BlockchainService() = default;

    std::string submitTransaction(
            Transaction transaction
    ) {

        if (transaction.from.empty()) {
            return "REJECTED: sender address is required";
        }

        if (transaction.to.empty()) {
            return "REJECTED: destination address is required";
        }

        if (transaction.asset.empty()) {
            return "REJECTED: asset is required";
        }

        if (transaction.amount.empty()) {
            return "REJECTED: amount is required";
        }

        if (transaction.tenor.empty()) {
            return "REJECTED: tenor is required";
        }

        transaction.id =
            TransactionHasher::createId(transaction);

        transaction.status = "PENDING";

        transactionCounter++;

        return transaction.id;
    }

    const Blockchain& getBlockchain() const {
        return blockchain;
    }

    std::uint64_t getTransactionCount() const {
        return transactionCounter;
    }
};

}
