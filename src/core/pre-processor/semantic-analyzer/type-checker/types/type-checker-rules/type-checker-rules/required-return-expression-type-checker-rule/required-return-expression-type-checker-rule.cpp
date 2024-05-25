//
// Created by Johny Georges on 2024-05-25.
//

#include "required-return-expression-type-checker-rule.h"
#include "../../../../../../../../shared/utils/logger/logger.h"

RequiredReturnExpressionTypeCheckerRule::RequiredReturnExpressionTypeCheckerRule(TypeSignature* returnType) {
    _returnType = returnType;
}

TypeSignature* RequiredReturnExpressionTypeCheckerRule::getReturnType() {
    return _returnType;
}

OptionalReturnExpressionTypeCheckerRule* RequiredReturnExpressionTypeCheckerRule::convertToOptional() {
    return new OptionalReturnExpressionTypeCheckerRule(_returnType);
}

TypeCheckerRuleType RequiredReturnExpressionTypeCheckerRule::getType() {
    return REQUIRED_RETURN_EXPRESSION_TCR;
}

std::string RequiredReturnExpressionTypeCheckerRule::toString() {
    return "BLOCK_HAS_RETURN_EXPRESSION";
}

bool RequiredReturnExpressionTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    if (this->getType() != other->getType()) {
        return false;
    }

    auto otherRule = (RequiredReturnExpressionTypeCheckerRule*)other;
    return this->getReturnType()->isEqualTo(otherRule->getReturnType());

}

void RequiredReturnExpressionTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
    _returnType->print();
    Logger::log("------------");
}