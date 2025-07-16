//
// Created by Johny Georges on 2024-05-29.
//

#include "identifier-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace IdentifierExpressionTypeCheckerPolicy {
    void apply(ASTIdentifierExpressionNode* identifierExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(identifierExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(identifierExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(identifierExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            identifierExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
    }
}