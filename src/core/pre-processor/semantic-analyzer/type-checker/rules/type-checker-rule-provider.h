//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_PROVIDER_H
#define JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

#include "type-checker-rules/no-return-expression-type-checker-rule/no-return-expression-type-checker-rule.h"
#include "type-checker-rules/required-return-expression-type-checker-rule/required-return-expression-type-checker-rule.h"

class TypeCheckerRuleProvider {
private:
    NoReturnExpressionTypeCheckerRule* _noReturnExpressionTypeCheckerRule;
    RequiredReturnExpressionTypeCheckerRule* _requiredReturnExpressionTypeCheckerRule;
public:
    TypeCheckerRuleProvider();
    NoReturnExpressionTypeCheckerRule* getNoReturnExpressionTypeCheckerRule();
    RequiredReturnExpressionTypeCheckerRule* getRequiredReturnExpressionTypeCheckerRule();

};
#endif //JETLANG_TYPE_CHECKER_RULE_PROVIDER_H
