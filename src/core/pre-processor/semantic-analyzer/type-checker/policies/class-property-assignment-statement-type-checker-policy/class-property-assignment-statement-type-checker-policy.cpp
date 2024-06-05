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
            TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertyAssignmentStatementNode),
            TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertyAssignmentStatementNode),
            TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertyAssignmentStatementNode),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertyAssignmentStatementNode->getExpression()),
            TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertyAssignmentStatementNode->getExpression()),
            TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertyAssignmentStatementNode->getExpression()),
            typeCheckerResult
        );

        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ClassPropertyAssignmentTypeMismatch(classPropertyAssignmentStatementNode),
            typeCheckerResult
        );
    }
}