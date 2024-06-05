//
// Created by Johny Georges on 2024-05-28.
//

#include "array-access-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace ArrayAccessExpressionTypeCheckerPolicy {
    void apply(ASTArrayAccessExpressionNode* arrayAccessExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayAccessExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessExpression),
            typeCheckerResult
        );
    }
}