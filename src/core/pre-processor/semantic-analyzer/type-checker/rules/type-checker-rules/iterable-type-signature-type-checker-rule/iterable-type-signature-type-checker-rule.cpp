//
// Created by Johny Georges on 2024-05-27.
//

#include "iterable-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void IterableTypeSignatureTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        typeCheckerResult->addError(message());
    }
}

TypeCheckerRuleType IterableTypeSignatureTypeCheckerRule::getType() {
    return ITERABLE_TYPE_SIGNATURE_TCR;
}

std::string IterableTypeSignatureTypeCheckerRule::toString() {
    return "ITERABLE_TYPE_SIGNATURE";
}

bool IterableTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void IterableTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}
