//
// Created by Johny Georges on 2024-05-28.
//

#include "binary-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace BinaryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTBinaryArithmeticExpressionNode> binaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(binaryExpression->getLeftNode(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(binaryExpression->getRightNode(), typeCheckerResult, fileScope);
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
                binaryExpression->getLeftTypeSignature(),
                binaryExpression->getRightTypeSignature(),
                mismatchTypeErrorMessage,
                typeCheckerResult
        );
    }

    void apply(std::shared_ptr<ASTBinaryComparatorExpressionNode> binaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(binaryExpression->getLeftNode(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(binaryExpression->getRightNode(), typeCheckerResult, fileScope);
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
            binaryExpression->getLeftTypeSignature(),
            binaryExpression->getRightTypeSignature(),
            mismatchTypeErrorMessage,
            typeCheckerResult
        );
    }
}