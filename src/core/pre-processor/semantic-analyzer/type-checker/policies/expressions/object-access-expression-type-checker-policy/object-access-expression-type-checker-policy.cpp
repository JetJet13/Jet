//
// Created by Johny Georges on 2024-05-29.
//

#include "object-access-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ObjectAccessExpressionTypeCheckerPolicy {
    void apply(ASTObjectAccessExpressionNode* objectAccessExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            objectAccessExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessExpression),
            typeCheckerResult
        );
    }
}