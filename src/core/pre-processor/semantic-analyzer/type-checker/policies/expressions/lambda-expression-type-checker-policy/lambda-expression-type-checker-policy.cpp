//
// Created by Johny Georges on 2024-05-29.
//

#include "lambda-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"
#include "../../../../../../../shared/utils/logger/logger.h"

namespace LambdaExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(lambdaExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(lambdaExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(lambdaExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            lambdaExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(lambdaExpression->getParameters(), typeCheckerResult, fileScope);
        if (lambdaExpression->getLambdaTypeSignature()->getReturnType()->isVoid()) {
            auto notAllPathsReturn = TypeCheckerErrorMessageTable::LambdaExpressionNotAllPathsReturn(lambdaExpression);
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                    lambdaExpression->getBlock(),
                    notAllPathsReturn,
                    typeCheckerResult
            );
        } else {
            auto returnTypeUnknown = TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeUnknown(lambdaExpression);
            auto returnTypeInvalid = TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeInvalid(lambdaExpression);
            TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
            ->enforce(
                lambdaExpression->getLambdaTypeSignature()->getReturnType(),
                returnTypeUnknown,
                returnTypeInvalid,
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                lambdaExpression->getLambdaTypeSignature()->getReturnType(),
                typeCheckerResult
            );
            auto notAllPathsReturn = TypeCheckerErrorMessageTable::LambdaExpressionNotAllPathsReturn(lambdaExpression);
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                notAllPathsReturn,
                typeCheckerResult
            );
        }
        TypeChecker::applyPolicyTo(lambdaExpression->getBlock(), typeCheckerResult, fileScope);
    }

    void apply(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(lambdaExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(lambdaExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(lambdaExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            lambdaExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(lambdaExpression->getParameters(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(lambdaExpression->getReturnExpression()->getExpression(), typeCheckerResult, fileScope);
    }
}