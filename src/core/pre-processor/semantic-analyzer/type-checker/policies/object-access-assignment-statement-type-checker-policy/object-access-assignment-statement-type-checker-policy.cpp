//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace ObjectAccessAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> objectAccessAssignmentStatementNode, TypeCheckerResult* typeCheckerResult) {
        auto statementUnknownMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeUnknown(objectAccessAssignmentStatementNode);
        auto statementInvalidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeInvalid(objectAccessAssignmentStatementNode);
        auto statementVoidMessage = TypeCheckerErrorMessageTable::ObjectPropertyTypeVoid(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        objectAccessAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
                        statementUnknownMessage,
                        statementInvalidMessage,
                        statementVoidMessage,
                        typeCheckerResult
                );

        auto expressionUnknownMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(objectAccessAssignmentStatementNode);
        auto expressionInvalidMessage = TypeCheckerErrorMessageTable::ExpressionTypeInvalid(objectAccessAssignmentStatementNode);
        auto expressionVoidMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            objectAccessAssignmentStatementNode->getExpression()->getTypeSignature(),
            expressionUnknownMessage,
            expressionInvalidMessage,
            expressionVoidMessage,
            typeCheckerResult
        );

        auto mismatchMessage = TypeCheckerErrorMessageTable::ObjectAccessAssignmentTypeMismatch(objectAccessAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            objectAccessAssignmentStatementNode->getObjectAccessAssignment()->getTypeSignature(),
            objectAccessAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            mismatchMessage,
            typeCheckerResult
        );
    }
}