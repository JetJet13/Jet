//
// Created by Johny Georges on 2024-05-29.
//

#include "function-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../type-checker.h"

namespace FunctionInvocationExpressionTypeCheckerPolicy {
    void apply(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(functionInvocationExpression->getArguments(), typeCheckerResult);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(functionInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(functionInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getReturnType(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(functionInvocationExpression);
        auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(functionInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes()->size(),
            functionInvocationExpression->getArguments()->numArguments(),
            functionInvocationExpression->getTypeSignature()->getFunctionType()->hasVariableLengthParameters(),
            notEnoughArgumentsMessage,
            tooManyArgumentsMessage,
            typeCheckerResult
        );

        if (!argumentListCountResultOk) {
            return;
        }

        auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(functionInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getTypeSignature()->getFunctionType()->getParameterTypes(),
            functionInvocationExpression->getArguments(),
            argumentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}