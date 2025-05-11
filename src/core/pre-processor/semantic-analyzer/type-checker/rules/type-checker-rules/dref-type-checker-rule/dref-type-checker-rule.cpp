//
// Created by Johny Georges on 2025-02-08.
//

#include "dref-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void DrefTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, std::string invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage);
    }
}

TypeCheckerRuleType DrefTypeSignatureTypeCheckerRule::getType() {
    return DREF_TYPE_SIGNATURE_TCR;
}

std::string DrefTypeSignatureTypeCheckerRule::toString() {
    return "DREF_TYPE_SIGNATURE";
}

bool DrefTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void DrefTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}