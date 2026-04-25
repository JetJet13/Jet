//
// Created by Johny Georges on 2024-05-28.
//

#include "class-property-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertyAssignmentStatementTypeCheckerPolicy {
    void apply(ASTClassPropertyAssignmentStatementNode* classPropertyAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertyAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertyAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertyAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertyAssignmentStatementNode->getExpression());
        auto invalidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertyAssignmentStatementNode->getExpression());
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertyAssignmentStatementNode->getExpression());
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassPropertyAssignmentTypeMismatch(classPropertyAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            classPropertyAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            classPropertyAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            assignmentTypeMismatchMessage,
            typeCheckerResult
        );
    }
}