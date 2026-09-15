#pragma once

#include "Block.hpp"
#include "../ledger/Genesis.hpp"
#include "../ledger/GenesisBuilder.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace cryptora {

class Blockchain {

private:

    std::vector<Block> chain;

public:

    Blockchain() {
        createGenesisBlock();
    }

    const std::vector<Block>& getChain() const {
        return chain;
    }

    const Block& latestBlock() const {
        return chain.back();
    }

    std::size_t height() const {
        return chain.size();
    }

    void addBlock(const Block& block) {

        if (block.height != chain.size()) {
            return;
        }

        if (block.previousHash != chain.back().hash) {
            return;
        }

        chain.push_back(block);
    }

    bool replaceChain(
            const std::vector<Block>& newChain
    ) {

        if (newChain.empty()) {
            return false;
        }

        if (newChain.front().height != 0) {
            return false;
        }

        if (newChain.front().previousHash != "0") {
            return false;
        }

        for (
            std::size_t i = 1;
            i < newChain.size();
            ++i
        ) {

            if (newChain[i].height != i) {
                return false;
            }

            if (newChain[i].previousHash !=
                newChain[i - 1].hash) {

                return false;
            }
        }

        chain = newChain;

        return true;
    }

private:

    void createGenesisBlock() {

        GenesisAllocation allocation;

        allocation.address =
            "CRYPTORA_GENESIS";

        allocation.amount = 21000000;

        Block genesis =
            GenesisBuilder::create(
                allocation
            );

        chain.push_back(genesis);
    }
};

}
