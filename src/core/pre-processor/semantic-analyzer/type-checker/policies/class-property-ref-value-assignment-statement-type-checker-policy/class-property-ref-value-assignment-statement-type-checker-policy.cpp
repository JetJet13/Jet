//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-ref-value-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ClassPropertyRefValueAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTClassPropertyRefValueAssignmentStatementNode> classPropertyRefValueAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto unknownMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeUnknown(classPropertyRefValueAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeInvalid(classPropertyRefValueAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::ClassPropertyTypeVoid(classPropertyRefValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(classPropertyRefValueAssignmentStatementNode->getExpression());
        auto invalidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(classPropertyRefValueAssignmentStatementNode->getExpression());
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(classPropertyRefValueAssignmentStatementNode->getExpression());
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            classPropertyRefValueAssignmentStatementNode->getExpression()->getTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto classPropertyTypeInvalidMessage = TypeCheckerErrorMessageTable::ClassPropertyRefValueAssignmentTypeInvalid(classPropertyRefValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
        ->enforce(
                classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature(),
                classPropertyTypeInvalidMessage,
                typeCheckerResult
        );

        if (!classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
            return;
        }
        auto assignmentRefTypeSignature = std::dynamic_pointer_cast<RefTypeSignature>(classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->getTypeSignature());
        auto assignmentTypeMismatchMessage = TypeCheckerErrorMessageTable::ClassPropertyRefValueAssignmentTypeMismatch(classPropertyRefValueAssignmentStatementNode);
        TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule()
        ->enforce(
                assignmentRefTypeSignature,
                classPropertyRefValueAssignmentStatementNode->getExpression()->getTypeSignature(),
                assignmentTypeMismatchMessage,
                typeCheckerResult
        );
    }
}