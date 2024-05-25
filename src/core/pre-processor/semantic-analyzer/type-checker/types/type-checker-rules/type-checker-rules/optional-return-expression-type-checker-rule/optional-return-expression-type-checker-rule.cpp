//
// Created by Johny Georges on 2024-05-25.
//

#include "optional-return-expression-type-checker-rule.h"
#include "../../../../../../../../shared/utils/logger/logger.h"

OptionalReturnExpressionTypeCheckerRule::OptionalReturnExpressionTypeCheckerRule(TypeSignature* returnType) {
    _returnType = returnType;
}

TypeSignature* OptionalReturnExpressionTypeCheckerRule::getReturnType() {
    return _returnType;
}

TypeCheckerRuleType OptionalReturnExpressionTypeCheckerRule::getType() {
    return OPTIONAL_RETURN_EXPRESSION_TCR;
}

std::string OptionalReturnExpressionTypeCheckerRule::toString() {
    return "OPTIONAL_RETURN_EXPRESSION";
}

bool OptionalReturnExpressionTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    if (this->getType() != other->getType()) {
        return false;
    }

    auto otherRule = (OptionalReturnExpressionTypeCheckerRule*)other;
    return this->getReturnType()->isEqualTo(otherRule->getReturnType());
}

void OptionalReturnExpressionTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
    _returnType->print();
    Logger::log("------------");
}