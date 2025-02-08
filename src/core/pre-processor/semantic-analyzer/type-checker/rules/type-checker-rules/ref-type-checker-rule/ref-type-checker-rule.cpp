//
// Created by Johny Georges on 2025-02-08.
//

#include "ref-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void RefTypeSignatureTypeCheckerRule::enforce(PointerTypeSignature* typeSignature, std::string invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->getUnderlyingType()->typeSourceIs(POINTER_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage);
    }
}

TypeCheckerRuleType RefTypeSignatureTypeCheckerRule::getType() {
    return REF_TYPE_SIGNATURE_TCR;
}

std::string RefTypeSignatureTypeCheckerRule::toString() {
    return "REF_TYPE_SIGNATURE";
}

bool RefTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void RefTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}