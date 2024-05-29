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
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterList()->numParameters(),
            functionInvocationExpression->getArguments()->numArguments(),
            TypeCheckerErrorMessageTable::ClassMethodCallNotEnoughArguments,
            TypeCheckerErrorMessageTable::ClassMethodCallTooManyArguments,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterList(),
            functionInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::ClassMethodCallArgumentTypeMismatch,
            typeCheckerResult
        );

    }
}