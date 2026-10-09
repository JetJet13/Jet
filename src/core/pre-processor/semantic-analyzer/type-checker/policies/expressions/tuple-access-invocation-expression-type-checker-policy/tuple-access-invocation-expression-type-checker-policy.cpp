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