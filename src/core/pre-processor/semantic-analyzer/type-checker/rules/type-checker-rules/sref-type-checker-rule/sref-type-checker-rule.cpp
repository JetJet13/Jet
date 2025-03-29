//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void SrefTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, std::string invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeSourceIs(POINTER_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage);
    }
}

TypeCheckerRuleType SrefTypeSignatureTypeCheckerRule::getType() {
    return SREF_TYPE_SIGNATURE_TCR;
}

std::string SrefTypeSignatureTypeCheckerRule::toString() {
    return "SREF_TYPE_SIGNATURE";
}

bool SrefTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void SrefTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}