//
// Created by Johny Georges on 2026-07-11.
//

#include "shared-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void SharedTypeSignatureTypeCheckerRule::enforce(std::shared_ptr<SharedTypeSignature> typeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->getUnderlyingType()->typeSourceIs(SHARED_TYPE_SOURCE)) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType SharedTypeSignatureTypeCheckerRule::getType() {
    return SHARED_TYPE_SIGNATURE_TCR;
}

std::string SharedTypeSignatureTypeCheckerRule::toString() {
    return "SHARED_TYPE_SIGNATURE";
}

bool SharedTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void SharedTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}