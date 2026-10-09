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
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-checker-policy.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace DrefExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTDrefExpressionNode> drefExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(drefExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(drefExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(drefExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );
        auto drefInvalidMessage = TypeCheckerErrorMessageTable::DrefExpressionTypeInvalid(drefExpression);
        TypeCheckerRuleProvider::getDrefTypeSignatureTypeCheckerRule()
        ->enforce(
            drefExpression->getExpressionNode()->getTypeSignature(),
            drefInvalidMessage,
            typeCheckerResult
        );
        TypeChecker::applyPolicyTo(drefExpression->getExpressionNode(), typeCheckerResult, fileScope);
    }
}