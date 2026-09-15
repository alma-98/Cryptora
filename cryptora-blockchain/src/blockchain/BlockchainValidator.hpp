#pragma once

#include "Blockchain.hpp"

#include <string>

namespace cryptora {

class BlockchainValidator {

public:

    static bool validate(
            const Blockchain& blockchain
    ) {

        const auto& chain =
            blockchain.getChain();

        if (chain.empty()) {
            return false;
        }

        if (chain.front().height != 0) {
            return false;
        }

        if (chain.front().previousHash != "0") {
            return false;
        }

        if (chain.front().hash != "CRYPTORA_GENESIS") {
            return false;
        }

        for (std::size_t i = 1; i < chain.size(); ++i) {

            const Block& previous =
                chain[i - 1];

            const Block& current =
                chain[i];

            if (current.height != i) {
                return false;
            }

            if (current.previousHash !=
                previous.hash) {
                return false;
            }

            if (current.transactionIds.empty()) {
                return false;
            }

            if (current.hash.empty()) {
                return false;
            }
        }

        return true;
    }
};

}
