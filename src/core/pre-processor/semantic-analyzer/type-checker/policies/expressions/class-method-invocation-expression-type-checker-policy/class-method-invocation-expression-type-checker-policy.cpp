//
// Created by Johny Georges on 2024-05-28.
//

#include "class-method-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace ClassMethodInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassMethodInvocationExpressionNode> classMethodInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classMethodInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classMethodInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::ClassMethodCallNotEnoughArguments(classMethodInvocationExpression->getArguments());
        auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::ClassMethodCallTooManyArguments(classMethodInvocationExpression->getArguments());
        TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
                classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameters()->numParameters(),
                classMethodInvocationExpression->getArguments()->numArguments(),
                classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameters()->isVariableLength(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
        );

        auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassMethodCallArgumentTypeMismatch(classMethodInvocationExpression->getArguments());
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameterTypes(),
            classMethodInvocationExpression->getArguments(),
            argumentTypeMismatchMessage,
            typeCheckerResult
        );

    }
}