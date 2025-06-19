//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace TupleAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessInvocationExpressionNode* tupleAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessInvocationExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessInvocationExpression),
            typeCheckerResult
        );
    }
}