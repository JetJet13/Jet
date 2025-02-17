//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ArrayAccessAssignmentStatementTypeCheckerPolicy {
    void apply(ASTArrayAccessAssignmentStatementNode* arrayAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        TypeCheckerErrorMessageTable::VariableTypeUnknown(
                                arrayAccessAssignmentStatementNode
                        ),
                        TypeCheckerErrorMessageTable::VariableTypeInvalid(
                                arrayAccessAssignmentStatementNode
                        ),
                        TypeCheckerErrorMessageTable::VariableTypeVoid(
                                arrayAccessAssignmentStatementNode
                        ),
                        typeCheckerResult
                );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        arrayAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
                        TypeCheckerErrorMessageTable::ExpressionTypeUnknown(
                                arrayAccessAssignmentStatementNode
                        ),
                        TypeCheckerErrorMessageTable::ExpressionTypeInvalid(
                                arrayAccessAssignmentStatementNode
                        ),
                        TypeCheckerErrorMessageTable::ExpressionTypeVoid(
                                arrayAccessAssignmentStatementNode
                        ),
                        typeCheckerResult
                );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
                ->enforce(
                        arrayAccessAssignmentStatementNode->getArrayAccessAssignment()->getTypeSignature(),
                        arrayAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
                        TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch(
                                arrayAccessAssignmentStatementNode
                        ),
                        typeCheckerResult
                );
    }
}