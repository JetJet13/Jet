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

#include "binary-expression-type-checker-policy.h"
#include "../../../rules/type-checker-rule-provider.h"
#include "../../../type-checker.h"

namespace BinaryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTBinaryArithmeticExpressionNode> binaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(binaryExpression->getLeftNode(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(binaryExpression->getRightNode(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(binaryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(binaryExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(binaryExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            binaryExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto mismatchTypeErrorMessage = TypeCheckerErrorMessageTable::BinaryExpressionOperandsTypeMismatch(binaryExpression);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
                binaryExpression->getLeftTypeSignature(),
                binaryExpression->getRightTypeSignature(),
                mismatchTypeErrorMessage,
                typeCheckerResult
        );
    }

    void apply(std::shared_ptr<ASTBinaryComparatorExpressionNode> binaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(binaryExpression->getLeftNode(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(binaryExpression->getRightNode(), typeCheckerResult, fileScope);
        auto unknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(binaryExpression);
        auto invalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(binaryExpression);
        auto voidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(binaryExpression);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            binaryExpression,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto mismatchTypeErrorMessage = TypeCheckerErrorMessageTable::BinaryExpressionOperandsTypeMismatch(binaryExpression);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            binaryExpression->getLeftTypeSignature(),
            binaryExpression->getRightTypeSignature(),
            mismatchTypeErrorMessage,
            typeCheckerResult
        );
    }
}