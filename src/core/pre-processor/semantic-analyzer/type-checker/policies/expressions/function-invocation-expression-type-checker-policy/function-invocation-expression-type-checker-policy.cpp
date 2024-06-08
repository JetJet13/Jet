//
// Created by Johny Georges on 2024-05-29.
//

#include "function-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace FunctionInvocationExpressionTypeCheckerPolicy {
    void apply(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getReturnType(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(functionInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(functionInvocationExpression),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes()->size(),
            functionInvocationExpression->getArguments()->numArguments(),
            TypeCheckerErrorMessageTable::ClassMethodCallNotEnoughArguments(functionInvocationExpression->getArguments()),
            TypeCheckerErrorMessageTable::ClassMethodCallTooManyArguments(functionInvocationExpression->getArguments()),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes(),
            functionInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::ClassMethodCallArgumentTypeMismatch(functionInvocationExpression),
            typeCheckerResult
        );

    }
}