//
// Created by Johny Georges on 2024-05-28.
//

#include "unique-type-signatures-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueTypeSignaturesTypeCheckerRule::enforce(std::vector<TypeSignature*>* typeSignatures, ErrorMessageLambda& nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto sameNames = std::vector<TypeSignature*>();
    for (unsigned long i = 0; i < typeSignatures->size(); ++i) {
        for (unsigned long j = i + 1; j < typeSignatures->size(); ++j) {
            auto typeSignature = typeSignatures->at(i);
            auto otherTypeSignature = typeSignatures->at(j);
            if (typeSignature->isEquivalentTo(otherTypeSignature)) {
                sameNames.push_back(typeSignature);
            }
        }
    }

    if (!sameNames.empty()) {
        typeCheckerResult->addError(nonUniqueMessage());
    }

}

TypeCheckerRuleType UniqueTypeSignaturesTypeCheckerRule::getType() {
    return UNIQUE_TYPE_SIGNATURES_TCR;
}

std::string UniqueTypeSignaturesTypeCheckerRule::toString() {
    return "UNIQUE_TYPE_SIGNATURES";
}

bool UniqueTypeSignaturesTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueTypeSignaturesTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}