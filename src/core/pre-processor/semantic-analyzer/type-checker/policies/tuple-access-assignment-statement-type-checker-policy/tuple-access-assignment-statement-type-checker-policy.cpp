//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace TupleAccessAssignmentStatementTypeCheckerPolicy {
    void apply(ASTTupleAccessAssignmentStatementNode* tupleAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(tupleAccessAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(tupleAccessAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(tupleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
            statementUnknownMessage,
            statementInvalidMessage,
            statementVoidMessage,
            typeCheckerResult
        );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(tupleAccessAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(tupleAccessAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(tupleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            tupleAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
            expressionUnknownMessage,
            expressionInvalidMessage,
            expressionVoidMessage,
            typeCheckerResult
        );

        auto mismatchMessage = TypeCheckerErrorMessageTable::TupleAccessAssignmentTypeMismatch(tupleAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            tupleAccessAssignmentStatementNode->getTupleAccessAssignment()->getTypeSignature(),
            tupleAccessAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            mismatchMessage,
            typeCheckerResult
        );
    }
}