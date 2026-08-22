//
// Created by Johny Georges on 2024-05-27.
//

#include "variable-assignment-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../rules/type-checker-rule-provider.h"

namespace VariableAssignmentStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTVariableAssignmentStatementNode> variableAssignmentStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto unknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(variableAssignmentStatementNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(variableAssignmentStatementNode);
        auto voidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(variableAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        auto unknownExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeUnknown(variableAssignmentStatementNode);
        auto invalidExpressionMessage =  TypeCheckerErrorMessageTable::ExpressionTypeInvalid(variableAssignmentStatementNode);
        auto voidExpressionMessage = TypeCheckerErrorMessageTable::ExpressionTypeVoid(variableAssignmentStatementNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            variableAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
            unknownExpressionMessage,
            invalidExpressionMessage,
            voidExpressionMessage,
            typeCheckerResult
        );

        auto typeMismatchMessage = TypeCheckerErrorMessageTable::VariableAssignmentTypeMismatch(variableAssignmentStatementNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
          variableAssignmentStatementNode->getVariableAssignment()->getTypeSignature(),
          variableAssignmentStatementNode->getExpression()->getTypeSignature()->getTargetTypeSignature(),
          typeMismatchMessage,
          typeCheckerResult
        );
    }
}