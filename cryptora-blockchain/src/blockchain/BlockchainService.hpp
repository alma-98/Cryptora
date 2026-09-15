#pragma once

#include "Blockchain.hpp"
#include "../crypto/TransactionHasher.hpp"
#include "../transaction/Transaction.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cryptora {

class BlockchainService {

private:

    Blockchain blockchain;

    std::uint64_t transactionCounter{0};

    std::unordered_map<std::string, Transaction>
        transactions;

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

        if (transaction.asset != "CRC") {
            return "REJECTED: unsupported native asset";
        }

        if (transaction.amount.empty()) {
            return "REJECTED: amount is required";
        }

        if (transaction.tenor.empty()) {
            return "REJECTED: tenor is required";
        }

        transaction.id =
            TransactionHasher::createId(
                transaction
            );

        transaction.status = "PENDING";

        if (transactions.find(transaction.id)
            != transactions.end()) {

            return transaction.id;
        }

        Block block;

        block.height =
            static_cast<std::uint64_t>(
                blockchain.height()
            );

        block.previousHash =
            blockchain.latestBlock().hash;

        block.timestamp =
            ++transactionCounter;

        block.transactionIds.push_back(
            transaction.id
        );

        block.hash =
            Hash::sha256(
                block.previousHash +
                "|" +
                transaction.id +
                "|" +
                std::to_string(block.timestamp)
            );

        blockchain.addBlock(block);

        transactions.emplace(
            transaction.id,
            transaction
        );

        return transaction.id;
    }

    const Transaction* getTransaction(
            const std::string& transactionId
    ) const {

        const auto iterator =
            transactions.find(transactionId);

        if (iterator == transactions.end()) {
            return nullptr;
        }

        return &iterator->second;
    }

    const Blockchain& getBlockchain() const {
        return blockchain;
    }

    std::uint64_t getTransactionCount() const {
        return transactionCounter;
    }
};

}
