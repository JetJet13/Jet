//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
#define JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"

class NoReturnExpressionTypeCheckerRule : public TypeCheckerRule {
public:
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
