//
// Created by Johny Georges on 2024-05-28.
//

#include "class-property-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertyAssignmentStatementTypeCheckerPolicy {
    void apply(ASTClassPropertyAssignmentStatementNode* classPropertyAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown,
            TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid,
            TypeCheckerErrorMessageTable::ClassPropertyTypeVoid,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown,
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid,
            TypeCheckerErrorMessageTable::ExpressionTypeVoid,
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ClassPropertyAssignmentTypeMismatch,
            typeCheckerResult
        );
    }
}