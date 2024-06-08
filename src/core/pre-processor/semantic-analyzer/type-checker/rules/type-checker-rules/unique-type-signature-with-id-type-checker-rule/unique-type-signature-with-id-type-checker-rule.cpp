//
// Created by Johny Georges on 2024-05-28.
//

#include "unique-type-signature-with-id-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueTypeSignatureWithIdTypeCheckerRule::enforce(std::vector<std::pair<std::string, TypeSignature*>>* pairs, std::string nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto samePairs = std::vector<std::pair<std::string, TypeSignature*>>();
    for (int i = 0; i < pairs->size(); ++i) {
        for (int j = i + 1; j < pairs->size(); ++j) {
            auto pair = pairs->at(i);
            auto otherPair = pairs->at(j);
            if (pair.first == otherPair.first && pair.second->isEquivalentTo(otherPair.second)) {
                samePairs.push_back(pair);
            }
        }
    }

    if (!samePairs.empty()) {
        typeCheckerResult->addError(nonUniqueMessage);
    }

}

TypeCheckerRuleType UniqueTypeSignatureWithIdTypeCheckerRule::getType() {
    return UNIQUE_TYPE_SIGNATURE_WITH_ID_TCR;
}

std::string UniqueTypeSignatureWithIdTypeCheckerRule::toString() {
    return "UNIQUE_TYPE_SIGNATURE_WITH_ID";
}

bool UniqueTypeSignatureWithIdTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueTypeSignatureWithIdTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}