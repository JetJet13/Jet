//
// Created by Johny Georges on 2024-05-29.
//

#include "lambda-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace LambdaExpressionTypeCheckerPolicy {
    void apply(ASTLambdaExpressionNode* lambdaExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            lambdaExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(lambdaExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(lambdaExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(lambdaExpression),
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(lambdaExpression->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(lambdaExpression->getBlock(), typeCheckerResult);
        if (lambdaExpression->getReturnType() && lambdaExpression->getTypeSignature()->getReturnType()) {
            TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
            ->enforce(
                lambdaExpression->getTypeSignature()->getReturnType(),
                TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeUnknown(lambdaExpression),
                TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeInvalid(lambdaExpression),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                lambdaExpression->getTypeSignature()->getReturnType(),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                TypeCheckerErrorMessageTable::LambdaExpressionNotAllPathsReturn(lambdaExpression),
                typeCheckerResult
            );
        } else {
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                lambdaExpression->getBlock(),
                TypeCheckerErrorMessageTable::LambdaExpressionNotAllPathsReturn(lambdaExpression),
                typeCheckerResult
            );
        }
    }
    void apply(ASTLambdaWithFatArrowExpressionNode* lambdaExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                    lambdaExpression,
                    TypeCheckerErrorMessageTable::ExpressionTypeUnknown(lambdaExpression),
                    TypeCheckerErrorMessageTable::ExpressionTypeInvalid(lambdaExpression),
                    TypeCheckerErrorMessageTable::ExpressionTypeVoid(lambdaExpression),
                    typeCheckerResult
                );
        TypeChecker::applyPolicyTo(lambdaExpression->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(lambdaExpression->getReturnExpression()->getExpression(), typeCheckerResult);
    }
}