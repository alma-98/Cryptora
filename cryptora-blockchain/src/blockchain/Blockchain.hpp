#pragma once

#include "Block.hpp"

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

private:

    void createGenesisBlock() {

        Block genesis;

        genesis.height = 0;
        genesis.previousHash = "0";
        genesis.timestamp = 0;
        genesis.hash = "CRYPTORA_GENESIS";

        chain.push_back(genesis);
    }
};

}