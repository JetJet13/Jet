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

        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes()->size(),
            functionInvocationExpression->getArguments()->numArguments(),
            TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(functionInvocationExpression),
            TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(functionInvocationExpression),
            typeCheckerResult
        );

        if (!argumentListCountResultOk) {
            return;
        }
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes(),
            functionInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(functionInvocationExpression),
            typeCheckerResult
        );
    }
}