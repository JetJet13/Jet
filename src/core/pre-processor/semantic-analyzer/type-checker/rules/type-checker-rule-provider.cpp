//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-provider.h"

TypeCheckerRuleProvider::TypeCheckerRuleProvider() {
    _noReturnExpressionTypeCheckerRule = new NoReturnExpressionTypeCheckerRule();
}

NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule() {
    return _noReturnExpressionTypeCheckerRule;
}

RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule() {
    return _requiredReturnExpressionTypeCheckerRule;
}