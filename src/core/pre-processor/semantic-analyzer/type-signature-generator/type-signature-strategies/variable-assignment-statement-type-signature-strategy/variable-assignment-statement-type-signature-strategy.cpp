//
// Created by Johny Georges on 2024-05-22.
//

#include "variable-assignment-statement-type-signature-strategy.h"

void VariableAssignmentStatementTypeSignatureStrategy::assign(ASTVariableAssignmentStatementNode* variableAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(variableAssignmentStatement->getExpression(), context, scope);
    variableAssignmentStatement->getVariableAssignment()->setTypeSignature(
        scope->find(
            variableAssignmentStatement
            ->getVariableAssignment()
            ->getIdentifierNode()
            ->getId()
        )
    );
}