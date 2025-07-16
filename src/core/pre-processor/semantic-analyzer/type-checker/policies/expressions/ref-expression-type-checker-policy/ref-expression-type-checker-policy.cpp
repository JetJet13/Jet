//
// Created by Johny Georges on 2025-02-01.
//

#include "ref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace RefExpressionTypeCheckerPolicy {
    void apply(ASTRefExpressionNode* refExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(refExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(refExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(refExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            refExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        auto refExpressionInvalidMessage = TypeCheckerErrorMessageTable::RefExpressionTypeInvalid(refExpression);
        TypeCheckerRuleProvider::getRefTypeSignatureTypeCheckerRule()
        ->enforce(
            refExpression->getTypeSignature(),
            refExpressionInvalidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(refExpression->getExpressionNode(), typeCheckerResult);
    }
}