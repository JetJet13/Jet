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
    }
}