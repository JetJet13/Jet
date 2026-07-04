//
// Created by Johny Georges on 2024-05-27.
//

#include "type-signature-mismatch-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void TypeSignatureMismatchTypeCheckerRule::enforce(std::optional<std::shared_ptr<ASTNode>> node, std::optional<std::shared_ptr<ASTNode>> otherNode, ErrorMessageLambda& mismatchMessage, TypeCheckerResult* typeCheckerResult) {
    if ((node && !otherNode) || (!node && otherNode)) {
        typeCheckerResult->addError(mismatchMessage());
        return;
    }

    this->enforce(node.value()->getTypeSignature(), otherNode.value()->getTypeSignature(), mismatchMessage, typeCheckerResult);

}

void TypeSignatureMismatchTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, std::shared_ptr<TypeSignature> otherTypeSignature, ErrorMessageLambda& mismatchMessage, TypeCheckerResult* typeCheckerResult) {
    if (!typeSignature->isEquivalentTo(otherTypeSignature)) {
        typeCheckerResult->addError(mismatchMessage());
    }
}

TypeCheckerRuleType TypeSignatureMismatchTypeCheckerRule::getType() {
    return TYPE_SIGNATURE_MISMATCH_TCR;
}

std::string TypeSignatureMismatchTypeCheckerRule::toString() {
    return "TYPE_SIGNATURE_MISMATCH";
}

bool TypeSignatureMismatchTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void TypeSignatureMismatchTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}