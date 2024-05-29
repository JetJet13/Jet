//
// Created by Johny Georges on 2024-05-28.
//

#include "binary-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace BinaryExpressionTypeCheckerPolicy {
    void apply(ASTBinaryExpressionNode* binaryExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            binaryExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );
    }
}