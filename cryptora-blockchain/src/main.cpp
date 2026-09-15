#include "blockchain/Blockchain.hpp"
#include "blockchain/BlockchainService.hpp"
#include "blockchain/BlockchainValidator.hpp"
#include "network/HttpServer.hpp"
#include "network/NodeConfig.hpp"
#include "transaction/Transaction.hpp"

#include <iostream>
#include <string>

int main() {

    cryptora::BlockchainService blockchainService;

    cryptora::HttpServer server(
        cryptora::NodeConfig::RPC_PORT
    );

    std::cout
        << "Cryptora Native Blockchain"
        << std::endl;

    std::cout
        << "Network: "
        << cryptora::NodeConfig::NETWORK
        << std::endl;

    std::cout
        << "Native Asset: "
        << cryptora::NodeConfig::NATIVE_ASSET
        << std::endl;

    std::cout
        << "Version: "
        << cryptora::NodeConfig::VERSION
        << std::endl;

    const bool started =
        server.start(
            [&](const std::string& method,
                const std::string& path,
                const std::string& body) -> std::string {

                if (method == "GET" &&
                    path == "/health") {

                    return
                        "{\"status\":\"UP\","
                        "\"network\":\"cryptora-native\","
                        "\"asset\":\"CRC\"}";
                }

                if (method == "GET" &&
                    path == "/chain") {

                    const auto& chain =
                        blockchainService
                            .getBlockchain()
                            .getChain();

                    const bool valid =
                        cryptora::BlockchainValidator::validate(
                            blockchainService.getBlockchain()
                        );

                    return
                        "{\"height\":" +
                        std::to_string(chain.size()) +
                        ",\"valid\":" +
                        (valid ? "true" : "false") +
                        "}";
                }

                if (method == "POST" &&
                    path == "/transactions") {

                    cryptora::Transaction transaction;

                    transaction.from = body;
                    transaction.to = body;
                    transaction.asset =
                        cryptora::NodeConfig::NATIVE_ASSET;
                    transaction.amount = "0";
                    transaction.tenor = "0";

                    const std::string result =
                        blockchainService
                            .submitTransaction(
                                transaction
                            );

                    return
                        "{\"transactionId\":\"" +
                        result +
                        "\"}";
                }

                return
                    "{\"error\":\"endpoint_not_found\"}";
            }
        );

    return started ? 0 : 1;
}
