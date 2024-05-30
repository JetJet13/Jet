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
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            TypeCheckerErrorMessageTable::VariableTypeInvalid(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            TypeCheckerErrorMessageTable::VariableTypeVoid(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
          variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
          variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch(
                variableAssignmentStatementNode->getVariableAssignment()->getIdentifierNode()->getLexeme()
            ),
            typeCheckerResult
        );
    }
}