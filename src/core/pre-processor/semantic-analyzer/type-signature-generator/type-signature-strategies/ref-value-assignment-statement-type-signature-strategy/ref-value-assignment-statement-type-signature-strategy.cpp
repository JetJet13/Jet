//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-statement-type-signature-strategy.h"

void RefValueAssignmentStatementTypeSignatureStrategy::assign(ASTRefValueAssignmentStatementNode* refValueAssignmentStatement, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(refValueAssignmentStatement->getExpression(), scope);
    refValueAssignmentStatement->getVariableAssignment()->setTypeSignature(
            scope->find(
                    refValueAssignmentStatement
                            ->getVariableAssignment()
                            ->getIdentifierNode()
                            ->getId()
            )
    );
}