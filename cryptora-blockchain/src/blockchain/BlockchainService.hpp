#pragma once

#include "Blockchain.hpp"
#include "BlockchainValidator.hpp"
#include "../crypto/Hash.hpp"
#include "../crypto/TransactionHasher.hpp"
#include "../ledger/CoinIssuer.hpp"
#include "../ledger/Ledger.hpp"
#include "../storage/BlockchainStorage.hpp"
#include "../transaction/Transaction.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

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

    static constexpr const char* TRANSACTION_STORAGE =
        "cryptora-transactions.dat";

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

        bool chainLoaded = false;

        if (storage.exists()) {

            std::vector<Block> loadedChain;

            if (storage.load(loadedChain) &&
                validateLoadedChain(loadedChain)) {

                chainLoaded =
                    blockchain.replaceChain(
                        loadedChain
                    );
            }
        }

        coinIssuer.issue(
            21000000
        );

        ledger.issue(
            GENESIS_ADDRESS,
            21000000
        );

        if (!chainLoaded) {

            storage.save(
                blockchain.getChain()
            );
        }

        loadTransactions();
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

        saveTransactions();

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

private:

    void saveTransactions() const {

        std::ofstream output(
            TRANSACTION_STORAGE,
            std::ios::trunc
        );

        if (!output.is_open()) {
            return;
        }

        for (const auto& entry : transactions) {

            const Transaction& tx = entry.second;

            output
                << tx.id << "|"
                << tx.from << "|"
                << tx.to << "|"
                << tx.asset << "|"
                << tx.amount << "|"
                << tx.tenor << "|"
                << tx.status
                << "\n";
        }
    }

    void loadTransactions() {

        std::ifstream input(
            TRANSACTION_STORAGE
        );

        if (!input.is_open()) {
            return;
        }

        std::string line;

        while (std::getline(input, line)) {

            if (line.empty()) {
                continue;
            }

            std::stringstream stream(line);
            std::vector<std::string> fields;
            std::string field;

            while (std::getline(stream, field, '|')) {
                fields.push_back(field);
            }

            if (fields.size() != 7) {
                continue;
            }

            Transaction tx;

            tx.id = fields[0];
            tx.from = fields[1];
            tx.to = fields[2];
            tx.asset = fields[3];
            tx.amount = fields[4];
            tx.tenor = fields[5];
            tx.status = fields[6];

            if (!tx.id.empty()) {
                transactions[tx.id] = tx;
            }
        }
    }

    static bool validateLoadedChain(
            const std::vector<Block>& chain
    ) {

        if (chain.empty()) {
            return false;
        }

        if (chain.front().height != 0) {
            return false;
        }

        if (chain.front().previousHash != "0") {
            return false;
        }

        for (std::size_t i = 1; i < chain.size(); ++i) {

            if (chain[i].height != i) {
                return false;
            }

            if (chain[i].previousHash !=
                chain[i - 1].hash) {

                return false;
            }

            if (chain[i].transactionIds.empty()) {
                return false;
            }
        }

        return true;
    }
};

}
