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

#include "class-property-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertySharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> classPropertySharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertySharedValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertySharedValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertySharedValueAssignmentStatementNode->getExpression());
        auto invalidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertySharedValueAssignmentStatementNode->getExpression());
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertySharedValueAssignmentStatementNode->getExpression());
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertySharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto classPropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::ClassPropertySharedValueAssignmentTypeInvalid(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
                classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
                classPropertyTypeInvalidMessage,
                typeCheckerResult
        );

        if (!classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassPropertySharedValueAssignmentTypeMismatch(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
                assignmentRefTypeSignature,
                classPropertySharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                assignmentTypeMismatchMessage,
                typeCheckerResult
        );
    }
}