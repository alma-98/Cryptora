#pragma once

#include "../blockchain/Block.hpp"

#include <fstream>
#include <sstream>
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

    bool load(
            std::vector<Block>& chain
    ) const {

        std::ifstream file(filePath);

        if (!file.is_open()) {
            return false;
        }

        std::vector<Block> loadedChain;

        std::string line;

        while (std::getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            std::stringstream stream(line);

            std::string height;
            std::string previousHash;
            std::string hash;
            std::string timestamp;
            std::string transactionIds;

            std::getline(
                stream,
                height,
                '|'
            );

            std::getline(
                stream,
                previousHash,
                '|'
            );

            std::getline(
                stream,
                hash,
                '|'
            );

            std::getline(
                stream,
                timestamp,
                '|'
            );

            std::getline(
                stream,
                transactionIds
            );

            try {

                Block block;

                block.height =
                    std::stoull(height);

                block.previousHash =
                    previousHash;

                block.hash =
                    hash;

                block.timestamp =
                    std::stoull(timestamp);

                std::stringstream idStream(
                    transactionIds
                );

                std::string transactionId;

                while (
                    std::getline(
                        idStream,
                        transactionId,
                        ',\
                    )
                ) {

                    if (!transactionId.empty()) {

                        block.transactionIds.push_back(
                            transactionId
                        );
                    }
                }

                loadedChain.push_back(
                    block
                );

            } catch (...) {

                return false;
            }
        }

        if (loadedChain.empty()) {
            return false;
        }

        chain = loadedChain;

        return true;
    }

    bool exists() const {

        std::ifstream file(filePath);

        return file.good();
    }
};

}
