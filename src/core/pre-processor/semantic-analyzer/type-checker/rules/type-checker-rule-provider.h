//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_PROVIDER_H
#define JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

#include "type-checker-rules/no-return-expression-type-checker-rule/no-return-expression-type-checker-rule.h"
#include "type-checker-rules/required-return-expression-type-checker-rule/required-return-expression-type-checker-rule.h"
#include "type-checker-rules/all-paths-return-type-checker-rule/all-paths-return-type-checker-rule.h"

class TypeCheckerRuleProvider {
private:
    static NoReturnExpressionTypeCheckerRule* _noReturnExpressionTypeCheckerRule;
    static RequiredReturnExpressionTypeCheckerRule* _requiredReturnExpressionTypeCheckerRule;
    static AllPathsReturnTypeCheckerRule* _allPathsReturnTypeCheckerRule;
public:
    static NoReturnExpressionTypeCheckerRule* getNoReturnExpressionTypeCheckerRule();
    static RequiredReturnExpressionTypeCheckerRule* getRequiredReturnExpressionTypeCheckerRule();
    static AllPathsReturnTypeCheckerRule* getAllPathsReturnTypeCheckerRule();
};

#endif //JETLANG_TYPE_CHECKER_RULE_PROVIDER_H
