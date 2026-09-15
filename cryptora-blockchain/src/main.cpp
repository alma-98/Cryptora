#include "blockchain/BlockchainService.hpp"
#include "blockchain/BlockchainValidator.hpp"
#include "network/HttpServer.hpp"
#include "network/NodeConfig.hpp"
#include "transaction/TransactionJsonParser.hpp"

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
        << "RPC Port: "
        << cryptora::NodeConfig::RPC_PORT
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

                if (method == "GET" &&
                    path.rfind("/wallet/", 0) == 0) {

                    const std::string address =
                        path.substr(
                            std::string("/wallet/").length()
                        );

                    if (address.empty()) {

                        return
                            "{\"error\":\"address_required\"}";
                    }

                    const long double balance =
                        blockchainService.getBalance(
                            address
                        );

                    return
                        "{\"address\":\"" +
                        address +
                        "\","
                        "\"asset\":\"CRC\","
                        "\"balance\":\"" +
                        std::to_string(balance) +
                        "\"}";
                }

                if (method == "GET" &&
                    path.rfind("/transactions/", 0) == 0) {

                    const std::string transactionId =
                        path.substr(
                            std::string("/transactions/").length()
                        );

                    if (transactionId.empty()) {

                        return
                            "{\"error\":\"transaction_id_required\"}";
                    }

                    const cryptora::Transaction* transaction =
                        blockchainService.getTransaction(
                            transactionId
                        );

                    if (transaction == nullptr) {

                        return
                            "{\"status\":\"NOT_FOUND\"}";
                    }

                    return
                        "{\"status\":\"FOUND\","
                        "\"transactionId\":\"" +
                        transaction->id +
                        "\","
                        "\"from\":\"" +
                        transaction->from +
                        "\","
                        "\"to\":\"" +
                        transaction->to +
                        "\","
                        "\"asset\":\"" +
                        transaction->asset +
                        "\","
                        "\"amount\":\"" +
                        transaction->amount +
                        "\","
                        "\"tenor\":\"" +
                        transaction->tenor +
                        "\","
                        "\"transactionStatus\":\"" +
                        transaction->status +
                        "\"}";
                }

                if (method == "POST" &&
                    path == "/transactions") {

                    cryptora::Transaction transaction =
                        cryptora::TransactionJsonParser::parse(
                            body
                        );

                    const std::string transactionId =
                        blockchainService.submitTransaction(
                            transaction
                        );

                    if (transactionId.rfind(
                            "REJECTED:",
                            0
                        ) == 0) {

                        return
                            "{\"status\":\"REJECTED\","
                            "\"message\":\"" +
                            transactionId +
                            "\"}";
                    }

                    return
                        "{\"status\":\"ACCEPTED\","
                        "\"transactionId\":\"" +
                        transactionId +
                        "\"}";
                }


                if (method == "POST" && path == "/") {

                    auto extractString =
                        [](const std::string& json,
                           const std::string& key) -> std::string {

                        const std::string token =
                            "\"" + key + "\"";

                        const std::size_t keyPos =
                            json.find(token);

                        if (keyPos == std::string::npos)
                            return "";

                        const std::size_t colon =
                            json.find(':',
                                      keyPos + token.length());

                        if (colon == std::string::npos)
                            return "";

                        std::size_t valueStart = colon + 1;

                        while (valueStart < json.length() &&
                               (json[valueStart] == ' ' ||
                                json[valueStart] == '\t' ||
                                json[valueStart] == '\n' ||
                                json[valueStart] == '\r')) {
                            ++valueStart;
                        }

                        if (valueStart >= json.length())
                            return "";

                        if (json[valueStart] == '"') {

                            const std::size_t firstQuote =
                                valueStart;

                            const std::size_t secondQuote =
                                json.find('"',
                                          firstQuote + 1);

                            if (secondQuote == std::string::npos)
                                return "";

                            return json.substr(
                                firstQuote + 1,
                                secondQuote - firstQuote - 1
                            );
                        }

                        std::size_t valueEnd =
                            valueStart;

                        while (valueEnd < json.length() &&
                               json[valueEnd] != ',' &&
                               json[valueEnd] != '}' &&
                               json[valueEnd] != ']') {
                            ++valueEnd;
                        }

                        std::string value =
                            json.substr(
                                valueStart,
                                valueEnd - valueStart
                            );

                        while (!value.empty() &&
                               (value.back() == ' ' ||
                                value.back() == '\t' ||
                                value.back() == '\n' ||
                                value.back() == '\r')) {
                            value.pop_back();
                        }

                        return value;
                    };

                    const std::string rpcMethod =
                        extractString(body, "method");

                    const std::string rpcId =
                        extractString(body, "id");

                    const std::string id =
                        rpcId.empty() ? "1" : rpcId;

                    if (rpcMethod == "cryptora_getTransaction" ||
                        rpcMethod == "eth_getTransactionByHash" ||
                        rpcMethod == "eth_getTransactionReceipt") {

                        std::string transactionId =
                            extractString(
                                body,
                                "transactionId"
                            );

                        if (transactionId.empty()) {
                            transactionId =
                                extractString(
                                    body,
                                    "hash"
                                );
                        }

                        if (transactionId.empty()) {

                            return
                                "{\"jsonrpc\":\"2.0\","
                                "\"id\":\"" + id + "\","
                                "\"error\":{"
                                "\"code\":-32602,"
                                "\"message\":"
                                "\"transaction hash is required\""
                                "}}";
                        }

                        const cryptora::Transaction* transaction =
                            blockchainService.getTransaction(
                                transactionId
                            );

                        if (transaction == nullptr) {

                            return
                                "{\"jsonrpc\":\"2.0\","
                                "\"id\":\"" + id + "\","
                                "\"result\":null}";
                        }

                        if (rpcMethod ==
                            "cryptora_getTransaction") {

                            return
                                "{\"jsonrpc\":\"2.0\","
                                "\"id\":\"" + id + "\","
                                "\"result\":{"
                                "\"transactionId\":\"" +
                                transaction->id +
                                "\","
                                "\"from\":\"" +
                                transaction->from +
                                "\","
                                "\"to\":\"" +
                                transaction->to +
                                "\","
                                "\"asset\":\"" +
                                transaction->asset +
                                "\","
                                "\"amount\":\"" +
                                transaction->amount +
                                "\","
                                "\"tenor\":\"" +
                                transaction->tenor +
                                "\","
                                "\"status\":\"" +
                                transaction->status +
                                "\"}}";
                        }

                        std::string blockNumber = "null";

                        const auto& chain =
                            blockchainService
                                .getBlockchain()
                                .getChain();

                        for (const auto& block : chain) {

                            for (const auto& txId :
                                 block.transactionIds) {

                                if (txId ==
                                    transaction->id) {

                                    blockNumber =
                                        "\"0x\"";

                                    break;
                                }
                            }

                            if (blockNumber != "null")
                                break;
                        }

                        if (rpcMethod ==
                            "eth_getTransactionByHash") {

                            return
                                "{\"jsonrpc\":\"2.0\","
                                "\"id\":\"" + id + "\","
                                "\"result\":{"
                                "\"hash\":\"" +
                                transaction->id +
                                "\","
                                "\"from\":\"" +
                                transaction->from +
                                "\","
                                "\"to\":\"" +
                                transaction->to +
                                "\","
                                "\"value\":\"" +
                                transaction->amount +
                                "\","
                                "\"asset\":\"" +
                                transaction->asset +
                                "\","
                                "\"tenor\":\"" +
                                transaction->tenor +
                                "\","
                                "\"blockNumber\":" +
                                blockNumber +
                                ","
                                "\"status\":\"" +
                                transaction->status +
                                "\"}}";
                        }

                        return
                            "{\"jsonrpc\":\"2.0\","
                            "\"id\":\"" + id + "\","
                            "\"result\":{"
                            "\"transactionHash\":\"" +
                            transaction->id +
                            "\","
                            "\"blockNumber\":" +
                            blockNumber +
                            ","
                            "\"status\":\"0x1\","
                            "\"from\":\"" +
                            transaction->from +
                            "\","
                            "\"to\":\"" +
                            transaction->to +
                            "\"}}";
                    }
                }

                return
                    "{\"error\":\"endpoint_not_found\"}";
            }
        );

    return started ? 0 : 1;
}
