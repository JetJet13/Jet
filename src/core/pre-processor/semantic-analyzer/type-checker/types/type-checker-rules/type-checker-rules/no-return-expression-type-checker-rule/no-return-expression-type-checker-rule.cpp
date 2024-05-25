//
// Created by Johny Georges on 2024-05-25.
//

#include "no-return-expression-type-checker-rule.h"
#include "../../../../../../../../shared/utils/logger/logger.h"

TypeCheckerRuleType NoReturnExpressionTypeCheckerRule::getType() {
    return NO_RETURN_EXPRESSION_TCR;
}

std::string NoReturnExpressionTypeCheckerRule::toString() {
    return "NO_RETURN_EXPRESSION";
}

bool NoReturnExpressionTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void NoReturnExpressionTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}