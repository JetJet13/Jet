//
// Created by Johny Georges on 2024-05-29.
//

#include "unary-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace UnaryExpressionTypeCheckerPolicy {
    void apply(ASTUnaryExpressionNode* unaryExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            unaryExpression->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(unaryExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(unaryExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(unaryExpression),
            typeCheckerResult
        );

        TypeChecker::applyPolicyTo(unaryExpression->getExpressionNode(), typeCheckerResult);
    }
}