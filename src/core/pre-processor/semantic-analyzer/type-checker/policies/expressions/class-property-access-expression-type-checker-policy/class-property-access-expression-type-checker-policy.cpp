//
// Created by Johny Georges on 2024-05-29.
//

#include "class-property-access-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace ClassPropertyAccessExpressionTypeCheckerPolicy {
    void apply(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAccessExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );
    }
}