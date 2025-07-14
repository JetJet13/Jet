//
// Created by Johny Georges on 2024-05-29.
//

#include "return-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ReturnTypeSignatureTypeCheckerRule::enforce(std::optional<ASTNode*> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (node) {
        this->enforce(node.value()->getTypeSignature(), unknownMessage, invalidMessage, typeCheckerResult);
    }
}

void ReturnTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->isUnknown()) {
        typeCheckerResult->addError(unknownMessage());
    } else if (typeSignature->isInvalid()) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType ReturnTypeSignatureTypeCheckerRule::getType() {
    return RETURN_TYPE_SIGNATURE_TCR;
}

std::string ReturnTypeSignatureTypeCheckerRule::toString() {
    return "RETURN_TYPE_SIGNATURE";
}

bool ReturnTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ReturnTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}