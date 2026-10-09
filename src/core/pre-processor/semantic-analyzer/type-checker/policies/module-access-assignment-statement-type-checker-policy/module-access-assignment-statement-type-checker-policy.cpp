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
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ModuleAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> moduleAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(moduleAccessAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(moduleAccessAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(moduleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            moduleAccessAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
            statementUnknownMessage,
            statementInvalidMessage,
            statementVoidMessage,
            typeCheckerResult
        );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(moduleAccessAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(moduleAccessAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(moduleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            moduleAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
            expressionUnknownMessage,
            expressionInvalidMessage,
            expressionVoidMessage,
            typeCheckerResult
        );

        auto mismatchMessage = TypeCheckerErrorMessageTable::ModuleAccessAssignmentTypeMismatch(moduleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            moduleAccessAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
            moduleAccessAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            mismatchMessage,
            typeCheckerResult
        );

        auto moduleName = moduleAccessAssignmentStatementNode->getModuleAccessAssignment()->getModuleAccess()->getModuleName();
        auto targetName = moduleAccessAssignmentStatementNode->getModuleAccessAssignment()->getModuleAccess()->getModuleTargetName();
        auto variableContext = fileScope->findVariableContext(moduleName, targetName);
        if (variableContext.value()->isConstant()) {
            auto variableAssignmentNotAllowedMessage = TypeCheckerErrorMessageTable::ModuleAccessAssignmentNotAllowed(moduleAccessAssignmentStatementNode);
            typeCheckerResult->addError(variableAssignmentNotAllowedMessage());
        }
    }
}