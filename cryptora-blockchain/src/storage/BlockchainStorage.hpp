#pragma once

#include "../blockchain/Block.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace cryptora {

class BlockchainStorage {

private:

    std::string filePath;

public:

    explicit BlockchainStorage(
            const std::string& path =
                "cryptora-chain.dat"
    )
        : filePath(path) {
    }

    bool save(
            const std::vector<Block>& chain
    ) const {

        std::ofstream file(
            filePath,
            std::ios::trunc
        );

        if (!file.is_open()) {
            return false;
        }

        for (const Block& block : chain) {

            file << block.height
                 << "|"
                 << block.previousHash
                 << "|"
                 << block.hash
                 << "|"
                 << block.timestamp
                 << "|";

            for (
                std::size_t i = 0;
                i < block.transactionIds.size();
                ++i
            ) {

                if (i > 0) {
                    file << ",";
                }

                file << block.transactionIds[i];
            }

            file << "\n";
        }

        return true;
    }

    bool exists() const {

        std::ifstream file(filePath);

        return file.good();
    }
};

}
