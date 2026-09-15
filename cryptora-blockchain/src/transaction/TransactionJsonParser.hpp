#pragma once

#include "Transaction.hpp"

#include <string>

namespace cryptora {

class TransactionJsonParser {

public:

    static Transaction parse(
            const std::string& json
    ) {

        Transaction transaction;

        transaction.from =
            getValue(json, "from");

        transaction.to =
            getValue(json, "to");

        transaction.asset =
            getValue(json, "asset");

        transaction.amount =
            getValue(json, "amount");

        transaction.tenor =
            getValue(json, "tenor");

        return transaction;
    }

private:

    static std::string getValue(
            const std::string& json,
            const std::string& key
    ) {

        const std::string token =
            "\"" + key + "\"";

        const std::size_t keyPosition =
            json.find(token);

        if (keyPosition == std::string::npos) {
            return "";
        }

        const std::size_t colon =
            json.find(
                ":",
                keyPosition + token.length()
            );

        if (colon == std::string::npos) {
            return "";
        }

        const std::size_t firstQuote =
            json.find(
                "\"",
                colon + 1
            );

        if (firstQuote == std::string::npos) {
            return "";
        }

        const std::size_t secondQuote =
            json.find(
                "\"",
                firstQuote + 1
            );

        if (secondQuote == std::string::npos) {
            return "";
        }

        return json.substr(
            firstQuote + 1,
            secondQuote - firstQuote - 1
        );
    }
};

}
