#pragma once

#include "../transaction/Transaction.hpp"

#include <string>

namespace cryptora {

struct GenesisAllocation {

    std::string address;

    long double amount{0};

    bool valid() const {

        return !address.empty() &&
               amount > 0;
    }
};

}
