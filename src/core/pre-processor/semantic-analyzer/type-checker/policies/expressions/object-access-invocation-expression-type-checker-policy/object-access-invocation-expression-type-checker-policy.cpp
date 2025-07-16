//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ObjectAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression,
                unknownMessage,
                invalidMessage,
                voidMessage,
                typeCheckerResult
        );
        auto invocableTypeSignature = (InvocableTypeSignature*)objectAccessInvocationExpression->getObjectAccess()->getTypeSignature();
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(objectAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(objectAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                         ->enforce(
                                            invocableTypeSignature->getParameterTypes()->size(),
                                            objectAccessInvocationExpression->getArguments()->numArguments(),
                                            notEnoughArguments,
                                            tooManyArguments,
                                            typeCheckerResult
                                         );

        if (!argumentListCountResultOk) {
            return;
        }
        auto argumentTypeMismatch = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getParameterTypes(),
            objectAccessInvocationExpression->getArguments(),
            argumentTypeMismatch,
            typeCheckerResult
        );
    }
}