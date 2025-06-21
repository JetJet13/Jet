//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ObjectAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
                objectAccessInvocationExpression,
                TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessInvocationExpression),
                TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessInvocationExpression),
                TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessInvocationExpression),
                typeCheckerResult
        );
        auto invocableTypeSignature = (InvocableTypeSignature*)objectAccessInvocationExpression->getObjectAccess()->getTypeSignature();
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                         ->enforce(
                                            invocableTypeSignature->getParameterTypes()->size(),
                                            objectAccessInvocationExpression->getArguments()->numArguments(),
                                            TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(objectAccessInvocationExpression),
                                            TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(objectAccessInvocationExpression),
                                            typeCheckerResult
                                         );

        if (!argumentListCountResultOk) {
            return;
        }
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getParameterTypes(),
            objectAccessInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(objectAccessInvocationExpression),
            typeCheckerResult
        );
    }
}