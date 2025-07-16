//
// Created by Johny Georges on 2024-05-29.
//

#include "unary-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace UnaryExpressionTypeCheckerPolicy {
    void apply(ASTUnaryExpressionNode* unaryExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(unaryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(unaryExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(unaryExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            unaryExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        TypeChecker::applyPolicyTo(unaryExpression->getExpressionNode(), typeCheckerResult);
    }
}