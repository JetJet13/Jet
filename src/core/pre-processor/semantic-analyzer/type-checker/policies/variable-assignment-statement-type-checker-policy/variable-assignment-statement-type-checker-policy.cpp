//
// Created by Johny Georges on 2024-05-27.
//

#include "variable-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace VariableAssignmentStatementTypeCheckerPolicy {
    void apply(ASTVariableAssignmentStatementNode* variableAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature()->print();

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            TypeCheckerErrorMessageTable::VariableTypeUnknown,
            TypeCheckerErrorMessageTable::VariableTypeInvalid,
            TypeCheckerErrorMessageTable::VariableTypeVoid,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
          variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
          variableAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch,
            typeCheckerResult
        );
    }
}