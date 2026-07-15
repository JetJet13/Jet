//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-ref-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ModuleAccessRefAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> moduleAccessRefAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(moduleAccessRefAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(moduleAccessRefAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(moduleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        moduleAccessRefAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(moduleAccessRefAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(moduleAccessRefAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(moduleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        moduleAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto moduleExportTypeInvalidMessage = TypeCheckerErrorMessageTable::ModuleAccessRefValueAssignmentTypeInvalid(moduleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        moduleAccessRefAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature(),
                        moduleExportTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!moduleAccessRefAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(moduleAccessRefAssignmentStatementNode->getModuleAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ModuleAccessRefValueAssignmentTypeMismatch(moduleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        moduleAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}