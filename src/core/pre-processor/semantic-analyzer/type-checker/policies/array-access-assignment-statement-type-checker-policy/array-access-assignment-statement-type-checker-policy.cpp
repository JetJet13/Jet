//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ArrayAccessAssignmentStatementTypeCheckerPolicy {
    void apply(ASTArrayAccessAssignmentStatementNode* arrayAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(arrayAccessAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(arrayAccessAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(arrayAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayAccessAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
            statementUnknownMessage,
            statementInvalidMessage,
            statementVoidMessage,
            typeCheckerResult
        );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            arrayAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
            expressionUnknownMessage,
            expressionInvalidMessage,
            expressionVoidMessage,
            typeCheckerResult
        );

        auto mismatchMessage = TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch(arrayAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
                arrayAccessAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                arrayAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
                mismatchMessage,
                typeCheckerResult
        );
    }
}