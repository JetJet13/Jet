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
// Created by Johny Georges on 2024-05-28.
//

#include "class-method-invocation-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"

namespace ClassMethodInvocationExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassMethodInvocationExpressionNode> classMethodInvocationExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classMethodInvocationExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classMethodInvocationExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::ClassMethodCallNotEnoughArguments(classMethodInvocationExpression->getArguments());
        auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::ClassMethodCallTooManyArguments(classMethodInvocationExpression->getArguments());
        TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
        ->enforce(
                classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameters()->numParameters(),
                classMethodInvocationExpression->getArguments()->numArguments(),
                classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameters()->isVariableLength(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
        );

        auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassMethodCallArgumentTypeMismatch(classMethodInvocationExpression->getArguments());
        TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classMethodInvocationExpression->getName()->getMethodTypeSignature()->getParameterTypes(),
            classMethodInvocationExpression->getArguments(),
            argumentTypeMismatchMessage,
            typeCheckerResult
        );

    }
}