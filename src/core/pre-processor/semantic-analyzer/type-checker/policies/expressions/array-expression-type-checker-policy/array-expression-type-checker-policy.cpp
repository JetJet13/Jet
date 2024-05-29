//
// Created by Johny Georges on 2024-05-28.
//

#include "array-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace ArrayExpressionTypeCheckerPolicy {
    void apply(ASTArrayExpressionNode* arrayExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayExpression->getTypeSignature()->getElementType(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );

        for (auto element : *arrayExpression->getElements()) {
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                arrayExpression->getTypeSignature()->getElementType(),
                element->getTypeSignature(),
                TypeCheckerErrorMessageTable::ArrayElementTypeMismatch,
                typeCheckerResult
            );
        }
    }
}