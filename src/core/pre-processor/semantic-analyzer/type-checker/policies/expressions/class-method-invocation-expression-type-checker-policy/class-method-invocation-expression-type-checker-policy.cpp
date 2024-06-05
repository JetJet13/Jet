//
// Created by Johny Georges on 2024-05-28.
//

#include "class-method-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"

namespace ClassMethodInvocationExpressionTypeCheckerPolicy {
    void apply(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classMethodInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classMethodInvocationExpression),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
                classMethodInvocationExpression->getName()->getTypeSignature()->getParameters()->numParameters(),
                classMethodInvocationExpression->getArguments()->numArguments(),
                TypeCheckerErrorMessageTable::ClassMethodCallNotEnoughArguments(classMethodInvocationExpression->getArguments()),
                TypeCheckerErrorMessageTable::ClassMethodCallTooManyArguments(classMethodInvocationExpression->getArguments()),
                typeCheckerResult
        );

        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getName()->getTypeSignature()->getParameters(),
            classMethodInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::ClassMethodCallArgumentTypeMismatch(classMethodInvocationExpression->getArguments()),
            typeCheckerResult
        );

    }
}