//
// Created by Johny Georges on 2025-10-07.
//

#include "invocable-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void InvocableTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->isInvocable()) {
        typeCheckerResult->addError(message());
    }
}

TypeCheckerRuleType InvocableTypeSignatureTypeCheckerRule::getType() {
    return INVOCABLE_TYPE_SIGNATURE_TCR;
}

std::string InvocableTypeSignatureTypeCheckerRule::toString() {
    return "INVOCABLE_TYPE_SIGNATURE";
}

bool InvocableTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void InvocableTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}