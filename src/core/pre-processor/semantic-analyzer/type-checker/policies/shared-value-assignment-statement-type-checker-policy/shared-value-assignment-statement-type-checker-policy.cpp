//
// Created by Johny Georges on 2026-02-18.
//

#include "shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace SharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTSharedValueAssignmentStatementNode> sharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(sharedValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(sharedValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
                        unknownMessage,
                        invalidMessage,
                        voidMessage,
                        typeCheckerResult
                );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(sharedValueAssignmentStatementNode);
        auto invalidExpressionMessage =  TypeCheckerErrorMessageTable::ExpressionTypeInvalid(sharedValueAssignmentStatementNode);
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            sharedValueAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto variableTypeInvalidMessage = TypeCheckerErrorMessageTable::SharedValueAssignmentTypeInvalid(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
            sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            variableTypeInvalidMessage,
            typeCheckerResult
        );

        if (!sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sharedValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::SharedValueAssignmentTypeMismatch(sharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
            assignmentRefTypeSignature,
            sharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            assignmentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}