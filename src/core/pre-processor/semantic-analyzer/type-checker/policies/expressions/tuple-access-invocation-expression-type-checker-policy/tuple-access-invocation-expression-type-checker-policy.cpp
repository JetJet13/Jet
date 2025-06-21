//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../../../type-signature/invocable-type-signature/invocable-type-signature.h"

namespace TupleAccessInvocationExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessInvocationExpressionNode* tupleAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessInvocationExpression,
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessInvocationExpression),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessInvocationExpression),
            typeCheckerResult
        );

        auto invocableTypeSignature = (InvocableTypeSignature*)tupleAccessInvocationExpression->getObjectAccess()->getTypeSignature();
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                            ->enforce(
                                                invocableTypeSignature->getParameterTypes()->size(),
                                                tupleAccessInvocationExpression->getArguments()->numArguments(),
                                                TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(tupleAccessInvocationExpression),
                                                TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(tupleAccessInvocationExpression),
                                                typeCheckerResult
                                            );

        if (!argumentListCountResultOk) {
            return;
        }
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            invocableTypeSignature->getParameterTypes(),
            tupleAccessInvocationExpression->getArguments(),
            TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(tupleAccessInvocationExpression),
            typeCheckerResult
        );
    }
}