//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../../../type-signature/invocable-type-signature/invocable-type-signature.h"

namespace TupleAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessInvocationExpressionNode* tupleAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessInvocationExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessInvocationExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto invocableTypeSignature = (InvocableTypeSignature*)tupleAccessInvocationExpression->getObjectAccess()->getTypeSignature();
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(tupleAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(tupleAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                            ->enforce(
                                                invocableTypeSignature->getParameterTypes()->size(),
                                                tupleAccessInvocationExpression->getArguments()->numArguments(),
                                                notEnoughArguments,
                                                tooManyArguments,
                                                typeCheckerResult
                                            );

        if (!argumentListCountResultOk) {
            return;
        }
        auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(tupleAccessInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getParameterTypes(),
            tupleAccessInvocationExpression->getArguments(),
            argumentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}