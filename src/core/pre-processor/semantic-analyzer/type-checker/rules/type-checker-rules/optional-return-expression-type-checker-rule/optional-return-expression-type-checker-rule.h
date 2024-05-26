//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_OPTIONAL_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
#define JETLANG_OPTIONAL_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"

class OptionalReturnExpressionTypeCheckerRule : public TypeCheckerRule {
private:
    TypeSignature* _returnType;
public:
    OptionalReturnExpressionTypeCheckerRule(TypeSignature* returnType);
    TypeSignature* getReturnType();
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_OPTIONAL_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
