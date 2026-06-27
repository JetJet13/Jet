//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-ref-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ArrayAccessRefAssignmentStatementTypeCheckerPolicy {
    void apply(ASTArrayAccessRefAssignmentStatementNode* arrayAccessRefAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ArrayElementTypeUnknown(arrayAccessRefAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeInvalid(arrayAccessRefAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeVoid(arrayAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessRefAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessRefAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessRefAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto arrayElementTypeInvalidMessage = TypeCheckerErrorMessageTable::ArrayAccessRefValueAssignmentTypeInvalid(arrayAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        arrayAccessRefAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        arrayElementTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!arrayAccessRefAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = (RefTypeSignature*)arrayAccessRefAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature();
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ArrayAccessRefValueAssignmentTypeMismatch(arrayAccessRefAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        arrayAccessRefAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}