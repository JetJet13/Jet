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
// Created by Johny Georges on 2026-02-18.
//

#include "shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace SharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTSharedValueAssignmentStatementNode> sharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(sharedValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(sharedValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
                        unknownMessage,
                        invalidMessage,
                        voidMessage,
                        typeCheckerResult
                );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(sharedValueAssignmentStatementNode);
        auto invalidExpressionMessage =  TypeCheckerErrorMessageTable::ExpressionTypeInvalid(sharedValueAssignmentStatementNode);
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            sharedValueAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto variableTypeInvalidMessage = TypeCheckerErrorMessageTable::SharedValueAssignmentTypeInvalid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
            sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            variableTypeInvalidMessage,
            typeCheckerResult
        );

        if (!sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::SharedValueAssignmentTypeMismatch(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
            assignmentRefTypeSignature,
            sharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            assignmentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}