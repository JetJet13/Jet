//
// Created by Johny Georges on 2025-06-28.
//

#include "unique-type-signature-keys-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueTypeSignatureKeysTypeCheckerRule::enforce(std::vector<std::string>* keys, ErrorMessageLambda& nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto sameKeys = std::vector<std::string>();
    for (int i = 0; i < keys->size(); ++i) {
        for (int j = i + 1; j < keys->size(); ++j) {
            auto key = keys->at(i);
            auto otherKey = keys->at(j);
            if (key == otherKey) {
                sameKeys.push_back(key);
            }
        }
    }

    if (!sameKeys.empty()) {
        typeCheckerResult->addError(nonUniqueMessage());
    }

}

TypeCheckerRuleType UniqueTypeSignatureKeysTypeCheckerRule::getType() {
    return UNIQUE_TYPE_SIGNATURE_KEYS_TCR;
}

std::string UniqueTypeSignatureKeysTypeCheckerRule::toString() {
    return "UNIQUE_TYPE_SIGNATURE_KEYS";
}

bool UniqueTypeSignatureKeysTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueTypeSignatureKeysTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}