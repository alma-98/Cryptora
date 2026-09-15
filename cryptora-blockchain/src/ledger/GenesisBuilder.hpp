#pragma once

#include "Genesis.hpp"
#include "../blockchain/Block.hpp"
#include "../crypto/Hash.hpp"

#include <string>

namespace cryptora {

class GenesisBuilder {

public:

    static Block create(
            const GenesisAllocation& allocation
    ) {

        Block genesis;

        genesis.height = 0;
        genesis.previousHash = "0";
        genesis.timestamp = 0;

        const std::string allocationData =
            allocation.address +
            "|" +
            std::to_string(allocation.amount);

        genesis.transactionIds.push_back(
            "GENESIS_ALLOCATION:" +
            allocationData
        );

        genesis.hash =
            Hash::sha256(
                "CRYPTORA_GENESIS|" +
                allocationData
            );

        return genesis;
    }
};

}
