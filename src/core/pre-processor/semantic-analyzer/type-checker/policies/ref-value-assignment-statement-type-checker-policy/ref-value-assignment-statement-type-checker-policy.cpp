//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace RefValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTRefValueAssignmentStatementNode> refValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(refValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(refValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(refValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        refValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
                        unknownMessage,
                        invalidMessage,
                        voidMessage,
                        typeCheckerResult
                );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(refValueAssignmentStatementNode);
        auto invalidExpressionMessage =  TypeCheckerErrorMessageTable::ExpressionTypeInvalid(refValueAssignmentStatementNode);
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(refValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            refValueAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto variableTypeInvalidMessage = TypeCheckerErrorMessageTable::RefValueAssignmentTypeInvalid(refValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
        ->enforce(
            refValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            variableTypeInvalidMessage,
            typeCheckerResult
        );

        if (!refValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<RefTypeSignature>(refValueAssignmentStatementNode->getVariableAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::RefValueAssignmentTypeMismatch(refValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
        ->enforce(
            assignmentRefTypeSignature,
            refValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            assignmentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}