//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"
#include "../../../../../../type-signature/invocable-type-signature/invocable-type-signature.h"

namespace ArrayAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> arrayAccessInvocationExpression, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(arrayAccessInvocationExpression->getArrayAccess(), typeCheckerResult);
        TypeChecker::applyPolicyTo(arrayAccessInvocationExpression->getArguments(), typeCheckerResult);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                    arrayAccessInvocationExpression,
                    unknownMessage,
                    invalidMessage,
                    typeCheckerResult
                );
        auto notInvocableMessage = TypeCheckerErrorMessageTable::NotInvocable(arrayAccessInvocationExpression->getArrayAccess());
        TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature(),
                        notInvocableMessage,
                        typeCheckerResult
                );

        if (!arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature()->isInvocable()) {
            return;
        }

        auto invocableTypeSignature = (InvocableTypeSignature*)arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature();
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(arrayAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(arrayAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                ->enforce(
                        invocableTypeSignature->getParameterTypes()->size(),
                        arrayAccessInvocationExpression->getArguments()->numArguments(),
                        invocableTypeSignature->hasVariableLengthParameters(),
                        notEnoughArguments,
                        tooManyArguments,
                        typeCheckerResult
                );

        if (!argumentListCountResultOk) {
            return;
        }

        auto unknownReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessInvocationExpression);
        auto invalidReturnTypeMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
                ->enforce(
                        invocableTypeSignature->getReturnType(),
                        unknownReturnTypeMessage,
                        invalidReturnTypeMessage,
                        typeCheckerResult
                );

        auto argumentTypeMismatch = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(arrayAccessInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
                ->enforce(
                        invocableTypeSignature->getParameterTypes(),
                        arrayAccessInvocationExpression->getArguments(),
                        argumentTypeMismatch,
                        typeCheckerResult
                );
    }
}