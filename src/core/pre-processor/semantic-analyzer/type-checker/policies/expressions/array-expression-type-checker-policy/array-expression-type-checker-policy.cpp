//
// Created by Johny Georges on 2024-05-28.
//

#include "array-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../../shared/utils/logger/logger.h"

namespace ArrayExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayExpressionNode> arrayExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayExpression->getArrayTypeSignature()->getElementType(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        for (auto element : *arrayExpression->getElements()) {
            auto mismatchMessage = TypeCheckerErrorMessageTable::ArrayElementTypeMismatch(element);
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                arrayExpression->getArrayTypeSignature()->getElementType(),
                element->getTypeSignature(),
                mismatchMessage,
                typeCheckerResult
            );
        }
    }
}