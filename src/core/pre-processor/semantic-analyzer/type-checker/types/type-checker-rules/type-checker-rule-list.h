//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_LIST_H
#define JETLANG_TYPE_CHECKER_RULE_LIST_H

#include <vector>
#include <optional>
#include "type-checker-rules/type-checker-rule.h"
#include "type-checker-rules/required-return-expression-type-checker-rule/required-return-expression-type-checker-rule.h"
#include "type-checker-rules/optional-return-expression-type-checker-rule/optional-return-expression-type-checker-rule.h"
#include "type-checker-rules/no-return-expression-type-checker-rule/no-return-expression-type-checker-rule.h"

class TypeCheckerRuleList {
private:
    std::vector<TypeCheckerRule*> _rules;
    std::optional<TypeCheckerRule*> find(TypeCheckerRuleType type);
public:
    TypeCheckerRuleList();
    explicit TypeCheckerRuleList(std::vector<TypeCheckerRule*> rules);
    explicit TypeCheckerRuleList(TypeCheckerRuleList* ruleList);
    std::vector<TypeCheckerRule*> getRules();
    void addRule(TypeCheckerRule* rule);
    void removeRule(TypeCheckerRule* rule);
    void removeRule(TypeCheckerRuleType type);
    void replaceRule(TypeCheckerRule* sourceRule, TypeCheckerRule* targetRule);
    TypeCheckerRuleList* combine(TypeCheckerRuleList* other);
    std::optional<RequiredReturnExpressionTypeCheckerRule*> findRequiredReturnExpressionRule();
    std::optional<OptionalReturnExpressionTypeCheckerRule*> findOptionalReturnExpressionRule();
    std::optional<NoReturnExpressionTypeCheckerRule*> findNoReturnExpressionRule();
};

#endif //JETLANG_TYPE_CHECKER_RULE_LIST_H
