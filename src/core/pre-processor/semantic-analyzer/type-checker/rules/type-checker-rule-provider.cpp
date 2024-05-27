//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-provider.h"

NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_noReturnExpressionTypeCheckerRule = new NoReturnExpressionTypeCheckerRule();
RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_requiredReturnExpressionTypeCheckerRule = new RequiredReturnExpressionTypeCheckerRule();
AllPathsReturnTypeCheckerRule* TypeCheckerRuleProvider::_allPathsReturnTypeCheckerRule = new AllPathsReturnTypeCheckerRule();

NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule() {
    return _noReturnExpressionTypeCheckerRule;
}

RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule() {
    return _requiredReturnExpressionTypeCheckerRule;
}

AllPathsReturnTypeCheckerRule* TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule() {
    return _allPathsReturnTypeCheckerRule;
}