//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ModuleAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> moduleAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(moduleAccessSharedValueAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(moduleAccessSharedValueAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(moduleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        moduleAccessSharedValueAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(moduleAccessSharedValueAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(moduleAccessSharedValueAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(moduleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        moduleAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto moduleExportTypeInvalidMessage = TypeCheckerErrorMessageTable::ModuleAccessSharedValueAssignmentTypeInvalid(moduleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        moduleAccessSharedValueAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
                        moduleExportTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!moduleAccessSharedValueAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(moduleAccessSharedValueAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ModuleAccessSharedValueAssignmentTypeMismatch(moduleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        moduleAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}