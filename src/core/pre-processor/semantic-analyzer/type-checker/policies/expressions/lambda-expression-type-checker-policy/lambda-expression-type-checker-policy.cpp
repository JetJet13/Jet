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
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(lambdaExpression->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(lambdaExpression->getBlock(), typeCheckerResult);
        if (lambdaExpression->getTypeSignature()->getReturnType()) {
            TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
            ->enforce(
                lambdaExpression->getTypeSignature()->getReturnType().value(),
                TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeUnknown,
                TypeCheckerErrorMessageTable::LambdaExpressionReturnTypeInvalid,
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                lambdaExpression->getTypeSignature()->getReturnType().value(),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()
            ->enforce(
                lambdaExpression->getBlock(),
                TypeCheckerErrorMessageTable::LambdaExpressionNotAllPathsReturn,
                typeCheckerResult
            );
        } else {
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                lambdaExpression->getBlock(),
                typeCheckerResult
            );
        }
    }
}