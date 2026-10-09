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

#include "new-class-instance-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace NewClassInstanceExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTNewClassInstanceExpressionNode> newClassInstanceExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(newClassInstanceExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(newClassInstanceExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(newClassInstanceExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            newClassInstanceExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        if (newClassInstanceExpression->getTypeSignature()->typeTargetIs(CLASS_TYPE_SOURCE)) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNotClassType(newClassInstanceExpression)());
        }

        if (!newClassInstanceExpression->getClassInstanceTypeSignature()->hasConstructorInfo()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::NewClassInstanceNoMatchingConstructor(newClassInstanceExpression)());
        }

        TypeChecker::applyPolicyTo(newClassInstanceExpression->getArguments(), typeCheckerResult, fileScope);
    }
}