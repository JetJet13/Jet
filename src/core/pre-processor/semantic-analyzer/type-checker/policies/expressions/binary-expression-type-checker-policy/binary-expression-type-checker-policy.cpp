//
// Created by Johny Georges on 2024-05-28.
//

#include "binary-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace BinaryExpressionTypeCheckerPolicy {
    void apply(ASTBinaryExpressionNode* binaryExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(binaryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(binaryExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(binaryExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            binaryExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto mismatchTypeErrorMessage = TypeCheckerErrorMessageTable::BinaryExpressionOperandsTypeMismatch(binaryExpression);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
                binaryExpression->getLeftNode()->getTypeSignature()->getTargetTypeSignature(),
                binaryExpression->getRightNode()->getTypeSignature()->getTargetTypeSignature(),
                mismatchTypeErrorMessage,
                typeCheckerResult
        );
    }
}