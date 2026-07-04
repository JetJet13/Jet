//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-ref-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace TupleAccessRefAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> tupleAccessRefAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(tupleAccessRefAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(tupleAccessRefAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(tupleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        tupleAccessRefAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessRefAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessRefAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        tupleAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto tuplePropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::TupleAccessRefValueAssignmentTypeInvalid(tupleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        tupleAccessRefAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
                        tuplePropertyTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!tupleAccessRefAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<RefTypeSignature>(tupleAccessRefAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::TupleAccessRefValueAssignmentTypeMismatch(tupleAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        tupleAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}