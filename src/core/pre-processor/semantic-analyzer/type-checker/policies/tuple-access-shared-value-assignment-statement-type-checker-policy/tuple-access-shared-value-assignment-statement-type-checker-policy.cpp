//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace TupleAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> tupleAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(tupleAccessSharedValueAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(tupleAccessSharedValueAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(tupleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        tupleAccessSharedValueAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessSharedValueAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessSharedValueAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        tupleAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto tuplePropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::TupleAccessSharedValueAssignmentTypeInvalid(tupleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        tupleAccessSharedValueAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
                        tuplePropertyTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!tupleAccessSharedValueAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(tupleAccessSharedValueAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::TupleAccessSharedValueAssignmentTypeMismatch(tupleAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        tupleAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}