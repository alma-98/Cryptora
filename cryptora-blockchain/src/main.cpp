#include "blockchain/Blockchain.hpp"
#include "blockchain/BlockchainService.hpp"
#include "blockchain/BlockchainValidator.hpp"

#include <iostream>

int main() {

    cryptora::BlockchainService blockchainService;

    std::cout << "Cryptora Native Blockchain" << std::endl;
    std::cout << "Network: cryptora-native" << std::endl;
    std::cout << "Native Asset: CRC" << std::endl;
    std::cout << "Genesis Height: "
              << blockchainService.getBlockchain().height() - 1
              << std::endl;

    const bool valid =
        cryptora::BlockchainValidator::validate(
            blockchainService.getBlockchain()
        );

    std::cout << "Chain Status: "
              << (valid ? "VALID" : "INVALID")
              << std::endl;

    std::cout << "Transaction Count: "
              << blockchainService.getTransactionCount()
              << std::endl;

    return valid ? 0 : 1;
}
