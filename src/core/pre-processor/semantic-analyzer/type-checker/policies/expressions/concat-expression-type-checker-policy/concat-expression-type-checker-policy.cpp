//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ConcatExpressionTypeCheckerPolicy {
    void apply(ASTConcatExpressionNode* concatExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                concatExpression,
                TypeCheckerErrorMessageTable::ExpressionTypeUnknown(concatExpression),
                TypeCheckerErrorMessageTable::ExpressionTypeInvalid(concatExpression),
                TypeCheckerErrorMessageTable::ExpressionTypeVoid(concatExpression),
                typeCheckerResult
        );
    }
}