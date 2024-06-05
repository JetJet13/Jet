//
// Created by Johny Georges on 2024-05-27.
//

#include "variable-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace VariableAssignmentStatementTypeCheckerPolicy {
    void apply(ASTVariableAssignmentStatementNode* variableAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            TypeCheckerErrorMessageTable::VariableTypeUnknown(
                variableAssignmentStatementNode
            ),
            TypeCheckerErrorMessageTable::VariableTypeInvalid(
                variableAssignmentStatementNode
            ),
            TypeCheckerErrorMessageTable::VariableTypeVoid(
                variableAssignmentStatementNode
            ),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(
                variableAssignmentStatementNode
            ),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(
                variableAssignmentStatementNode
            ),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(
                variableAssignmentStatementNode
            ),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
          variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
          variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch(
                variableAssignmentStatementNode
            ),
            typeCheckerResult
        );
    }
}