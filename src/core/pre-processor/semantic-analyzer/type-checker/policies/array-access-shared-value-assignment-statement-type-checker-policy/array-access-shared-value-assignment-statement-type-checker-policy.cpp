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
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ArrayAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> arrayAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ArrayElementTypeUnknown(arrayAccessSharedValueAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeVoid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessSharedValueAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto arrayElementTypeInvalidMessage = TypeCheckerErrorMessageTable::ArrayAccessSharedValueAssignmentTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        arrayElementTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ArrayAccessSharedValueAssignmentTypeMismatch(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        arrayAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}