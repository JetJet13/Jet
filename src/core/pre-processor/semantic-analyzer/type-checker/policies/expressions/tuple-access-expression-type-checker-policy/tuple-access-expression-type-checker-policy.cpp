//
// Created by Johny Georges on 2024-05-29.
//

#include "tuple-access-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace TupleAccessExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessExpression),
            typeCheckerResult
        );
    }
}