//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ArrayAccessSharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> arrayAccessSharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ArrayElementTypeUnknown(arrayAccessSharedValueAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ArrayElementTypeVoid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(arrayAccessSharedValueAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        expressionUnknownMessage,
                        expressionInvalidMessage,
                        expressionVoidMessage,
                        typeCheckerResult
                );

        auto arrayElementTypeInvalidMessage = TypeCheckerErrorMessageTable::ArrayAccessSharedValueAssignmentTypeInvalid(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        arrayElementTypeInvalidMessage,
                        typeCheckerResult
                );

        if (!arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(arrayAccessSharedValueAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ArrayAccessSharedValueAssignmentTypeMismatch(arrayAccessSharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
                ->enforce(
                        assignmentRefTypeSignature,
                        arrayAccessSharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                        assignmentTypeMismatchMessage,
                        typeCheckerResult
                );
    }
}