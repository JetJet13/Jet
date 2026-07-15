//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-shared-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertySharedValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> classPropertySharedValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertySharedValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertySharedValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertySharedValueAssignmentStatementNode->getExpression());
        auto invalidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertySharedValueAssignmentStatementNode->getExpression());
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertySharedValueAssignmentStatementNode->getExpression());
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertySharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto classPropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::ClassPropertySharedValueAssignmentTypeInvalid(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
                classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
                classPropertyTypeInvalidMessage,
                typeCheckerResult
        );

        if (!classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassPropertySharedValueAssignmentTypeMismatch(classPropertySharedValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule()
        ->enforce(
                assignmentRefTypeSignature,
                classPropertySharedValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                assignmentTypeMismatchMessage,
                typeCheckerResult
        );
    }
}