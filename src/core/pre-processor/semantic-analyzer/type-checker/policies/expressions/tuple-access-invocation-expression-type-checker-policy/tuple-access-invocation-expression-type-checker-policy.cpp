//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../../../../type-signature/invocable-type-signature/invocable-type-signature.h"
#include "../../../type-checker.h"

namespace TupleAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> tupleAccessInvocationExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(tupleAccessInvocationExpression->getArguments(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessInvocationExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessInvocationExpression,
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto notInvocableMessage = TypeCheckerErrorMessageTable::NotInvocable(tupleAccessInvocationExpression->getObjectAccess());
        TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule()
                ->enforce(
                        tupleAccessInvocationExpression->getObjectAccess()->getTypeSignature(),
                        notInvocableMessage,
                        typeCheckerResult
                );

        if (!tupleAccessInvocationExpression->getObjectAccess()->getTypeSignature()->isInvocable()) {
            return;
        }
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(tupleAccessInvocationExpression->getObjectAccess()->getTypeSignature());
        auto notEnoughArguments = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(tupleAccessInvocationExpression);
        auto tooManyArguments = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(tupleAccessInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
                                            ->enforce(
                                                invocableTypeSignature->getParameterTypes()->size(),
                                                tupleAccessInvocationExpression->getArguments()->numArguments(),
                                                invocableTypeSignature->hasVariableLengthParameters(),
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