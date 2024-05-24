//
// Created by Johny Georges on 2024-05-22.
//

#include "variable-assignment-statement-type-signature-strategy.h"

void VariableAssignmentStatementTypeSignatureStrategy::assign(ASTVariableAssignmentStatementNode* variableAssignmentStatement, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(variableAssignmentStatement->getExpression(), scope);
    variableAssignmentStatement->getVariableAssignment()->setTypeSignature(
        scope->find(
            variableAssignmentStatement
            ->getVariableAssignment()
            ->getIdentifierNode()
            ->getId()
        )
    );
}