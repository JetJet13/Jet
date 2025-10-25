//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../type-checker.h"

namespace ObjectAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(objectAccessInvocationExpression->getArguments(), typeCheckerResult);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression,
                unknownMessage,
                invalidMessage,
                typeCheckerResult
        );
        auto notInvocableMessage = TypeCheckerErrorMessageTable::NotInvocable(objectAccessInvocationExpression->getObjectAccess());
        TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression->getObjectAccess()->getTypeSignature(),
                notInvocableMessage,
                typeCheckerResult
        );

        if (!objectAccessInvocationExpression->getObjectAccess()->getTypeSignature()->isInvocable()) {
            return;
        }

        auto invocableTypeSignature = (InvocableTypeSignature*)objectAccessInvocationExpression->getObjectAccess()->getTypeSignature();
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(objectAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(objectAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                         ->enforce(
                                            invocableTypeSignature->getParameterTypes()->size(),
                                            objectAccessInvocationExpression->getArguments()->numArguments(),
                                            invocableTypeSignature->hasVariableLengthParameters(),
                                            notEnoughArguments,
                                            tooManyArguments,
                                            typeCheckerResult
                                         );

        if (!argumentListCountResultOk) {
            return;
        }

        auto unknownReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression);
        auto invalidReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getReturnType(),
            unknownReturnTypeMessage,
            invalidReturnTypeMessage,
            typeCheckerResult
        );

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