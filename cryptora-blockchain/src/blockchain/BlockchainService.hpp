#pragma once

#include "Blockchain.hpp"
#include "../crypto/Hash.hpp"
#include "../crypto/TransactionHasher.hpp"
#include "../ledger/CoinIssuer.hpp"
#include "../ledger/Ledger.hpp"
#include "../storage/BlockchainStorage.hpp"
#include "../transaction/Transaction.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cryptora {

class BlockchainService {

private:

    Blockchain blockchain;
    Ledger ledger;
    CoinIssuer coinIssuer;
    BlockchainStorage storage;

    std::uint64_t transactionCounter{0};

    std::unordered_map<std::string, Transaction>
        transactions;

    static constexpr const char* GENESIS_ADDRESS =
        "CRYPTORA_GENESIS";

public:

    BlockchainService()
        : storage("cryptora-chain.dat") {

        coinIssuer.initialize(
            "CRC",
            "Cryptora Coin",
            21000000
        );

        coinIssuer.issue(
            21000000
        );

        ledger.issue(
            GENESIS_ADDRESS,
            21000000
        );

        storage.save(
            blockchain.getChain()
        );
    }

    bool issueCoin(
            const std::string& address,
            long double amount
    ) {

        if (address.empty() ||
            amount <= 0) {

            return false;
        }

        if (!coinIssuer.issue(amount)) {
            return false;
        }

        if (!ledger.issue(
                address,
                amount
            )) {

            return false;
        }

        return storage.save(
            blockchain.getChain()
        );
    }

    std::string submitTransaction(
            Transaction transaction
    ) {

        if (transaction.from.empty()) {
            return "REJECTED: sender address is required";
        }

        if (transaction.to.empty()) {
            return "REJECTED: destination address is required";
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

        long double amount;

        try {

            amount =
                std::stold(transaction.amount);

        } catch (...) {

            return "REJECTED: invalid amount";
        }

        if (amount <= 0) {
            return "REJECTED: amount must be greater than zero";
        }

        transaction.id =
            TransactionHasher::createId(
                transaction
            );

        if (transactions.find(transaction.id)
            != transactions.end()) {

            return transaction.id;
        }

        if (ledger.getBalance(transaction.from)
            < amount) {

            return "REJECTED: insufficient balance";
        }

        transaction.status = "CONFIRMED";

        if (!ledger.applyTransaction(
                transaction
            )) {

            return "REJECTED: ledger update failed";
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

        if (!storage.save(
                blockchain.getChain()
            )) {

            return "REJECTED: blockchain storage failed";
        }

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

    long double getBalance(
            const std::string& address
    ) const {

        return ledger.getBalance(address);
    }

    const CoinState& getCoinState() const {
        return coinIssuer.getState();
    }

    const Blockchain& getBlockchain() const {
        return blockchain;
    }

    std::uint64_t getTransactionCount() const {
        return transactionCounter;
    }
};

}
