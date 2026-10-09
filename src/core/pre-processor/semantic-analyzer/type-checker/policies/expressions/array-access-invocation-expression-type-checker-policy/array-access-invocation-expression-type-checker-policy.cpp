// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"
#include "../../../../../../type-signature/invocable-type-signature/invocable-type-signature.h"

namespace ArrayAccessInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> arrayAccessInvocationExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(arrayAccessInvocationExpression->getArrayAccess(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(arrayAccessInvocationExpression->getArguments(), typeCheckerResult, fileScope);
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

        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature());
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