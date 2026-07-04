//
// Created by Johny Georges on 2024-05-27.
//

#include "defined-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void DefinedTypeSignatureTypeCheckerRule::enforce(std::optional<std::shared_ptr<ASTNode>> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, ErrorMessageLambda& voidMessage, TypeCheckerResult* typeCheckerResult) {
    if (node) {
        this->enforce(node.value()->getTypeSignature(), unknownMessage, invalidMessage, voidMessage, typeCheckerResult);
    }
}

void DefinedTypeSignatureTypeCheckerRule::enforce(std::optional<std::shared_ptr<ASTNode>> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (node) {
        this->enforce(node.value()->getTypeSignature(), unknownMessage, invalidMessage, typeCheckerResult);
    }
}

void DefinedTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, ErrorMessageLambda& voidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->isUnknown()) {
        typeCheckerResult->addError(unknownMessage());
    } else if (typeSignature->isInvalid()) {
        typeCheckerResult->addError(invalidMessage());
    } else if (typeSignature->isVoid()) {
        typeCheckerResult->addError(voidMessage());
    }
}

void DefinedTypeSignatureTypeCheckerRule::enforce(TypeSignature* typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->isUnknown()) {
        typeCheckerResult->addError(unknownMessage());
    } else if (typeSignature->isInvalid()) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType DefinedTypeSignatureTypeCheckerRule::getType() {
    return DEFINED_TYPE_SIGNATURE_TCR;
}

std::string DefinedTypeSignatureTypeCheckerRule::toString() {
    return "DEFINED_TYPE_SIGNATURE";
}

bool DefinedTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void DefinedTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}
