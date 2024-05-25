//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
#define JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../../type-signature/type-signature.h"
#include "../optional-return-expression-type-checker-rule/optional-return-expression-type-checker-rule.h"

class RequiredReturnExpressionTypeCheckerRule : public TypeCheckerRule {
private:
    TypeSignature* _returnType;
public:
    RequiredReturnExpressionTypeCheckerRule(TypeSignature* returnType);
    TypeSignature* getReturnType();
    OptionalReturnExpressionTypeCheckerRule* convertToOptional();
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
