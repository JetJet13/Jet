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

#include "curry-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

namespace CurryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTCurryExpressionNode> curryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(curryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(curryExpression);
        TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule()
        ->enforce(
            curryExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            typeCheckerResult
        );

        auto callableTypeSignature = curryExpression->getCallableExpression()->getTypeSignature();
        if (callableTypeSignature->typeTargetIs(FUNCTION_TYPE_SOURCE)) {
            auto parameterList = (std::dynamic_pointer_cast<FunctionTypeSignature>(callableTypeSignature))->getParameterList();
            auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments(curryExpression);
            auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallTooManyArguments(curryExpression);
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                parameterList->isVariableLength(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
            );

            auto argumentTypeMismatchMessage = TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch(curryExpression);
            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList->getParameterTypes(),
                curryExpression->getArguments(),
                argumentTypeMismatchMessage,
                typeCheckerResult
            );

        } else if (callableTypeSignature->typeTargetIs(CLASS_METHOD_TYPE_SOURCE)) {
            auto parameterList = (std::dynamic_pointer_cast<ClassMethodTypeSignature>(callableTypeSignature)->getParameters());
            auto notEnoughArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallNotEnoughArguments(curryExpression);
            auto tooManyArgumentsMessage = TypeCheckerErrorMessageTable::CurryCallTooManyArguments(curryExpression);
            TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule()
            ->enforce(
                parameterList->numParameters(),
                curryExpression->numArguments(),
                parameterList->isVariableLength(),
                notEnoughArgumentsMessage,
                tooManyArgumentsMessage,
                typeCheckerResult
            );

            auto argumentTypeMismatch = TypeCheckerErrorMessageTable::CurryCallArgumentTypeMismatch(curryExpression);
            TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                parameterList->getParameterTypes(),
                curryExpression->getArguments(),
                argumentTypeMismatch,
                typeCheckerResult
            );
        } else {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NotCallableCurryType(curryExpression)());
        }
    }
}