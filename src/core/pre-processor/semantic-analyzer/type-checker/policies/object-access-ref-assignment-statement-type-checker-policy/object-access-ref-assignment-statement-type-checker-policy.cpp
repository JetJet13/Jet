//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-ref-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ObjectAccessRefAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessRefAssignmentStatementNode> objectAccessRefAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(objectAccessRefAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(objectAccessRefAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(objectAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessRefAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessRefAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessRefAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto objectPropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::ObjectAccessRefValueAssignmentTypeInvalid(objectAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        objectAccessRefAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        objectPropertyTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!objectAccessRefAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<RefTypeSignature>(objectAccessRefAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ObjectAccessRefValueAssignmentTypeMismatch(objectAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        objectAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}