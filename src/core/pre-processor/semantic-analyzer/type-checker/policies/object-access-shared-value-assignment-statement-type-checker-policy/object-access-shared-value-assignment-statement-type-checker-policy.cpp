//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ObjectAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> objectAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(objectAccessSharedValueAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(objectAccessSharedValueAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(objectAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessSharedValueAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessSharedValueAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessSharedValueAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto objectPropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::ObjectAccessSharedValueAssignmentTypeInvalid(objectAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        objectAccessSharedValueAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        objectPropertyTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!objectAccessSharedValueAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(objectAccessSharedValueAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ObjectAccessSharedValueAssignmentTypeMismatch(objectAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        objectAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}