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

#include "class-property-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertyAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> classPropertyAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertyAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertyAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertyAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertyAssignmentStatementNode->getExpression());
        auto invalidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertyAssignmentStatementNode->getExpression());
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertyAssignmentStatementNode->getExpression());
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassPropertyAssignmentTypeMismatch(classPropertyAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            assignmentTypeMismatchMessage,
            typeCheckerResult
        );

        auto id = classPropertyAssignmentStatementNode->getPropertyAssignment()->getProperty()->getId();
        auto variableContext = fileScope->findVariableContext(id);
        if (variableContext.value()->isConstant()) {
            auto classPropertyAssignmentNotAllowedMessage = TypeCheckerErrorMessageTable::ClassPropertyAssignmentNotAllowed(classPropertyAssignmentStatementNode);
            typeCheckerResult->addError(classPropertyAssignmentNotAllowedMessage());
        }
    }
}