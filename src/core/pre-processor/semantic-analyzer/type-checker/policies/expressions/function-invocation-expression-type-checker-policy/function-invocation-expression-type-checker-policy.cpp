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
// Created by Johny Georges on 2024-05-29.
//

#include "function-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace FunctionInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionInvocationExpressionNode> functionInvocationExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(functionInvocationExpression->getArguments(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(functionInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(functionInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getInvocationTypeSignature()->getReturnType(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::FunctionCallNotEnoughArguments(functionInvocationExpression);
        auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::FunctionCallTooManyArguments(functionInvocationExpression);
        auto argumentListCountResultOk = TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getInvocationTypeSignature()->getFunctionType()->getParameterTypes()->size(),
            functionInvocationExpression->getArguments()->numArguments(),
            functionInvocationExpression->getInvocationTypeSignature()->getFunctionType()->hasVariableLengthParameters(),
            notEnoughArgumentsMessage,
            tooManyArgumentsMessage,
            typeCheckerResult
        );

        if (!argumentListCountResultOk) {
            return;
        }
        auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::FunctionCallArgumentTypeMismatch(functionInvocationExpression);
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            functionInvocationExpression->getInvocationTypeSignature()->getFunctionType()->getParameterTypes(),
            functionInvocationExpression->getArguments(),
            argumentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}