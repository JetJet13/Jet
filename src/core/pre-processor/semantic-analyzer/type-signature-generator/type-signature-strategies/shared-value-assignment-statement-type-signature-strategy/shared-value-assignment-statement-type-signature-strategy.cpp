//
// Created by Johny Georges on 2026-02-18.
//

#include "shared-value-assignment-statement-type-signature-strategy.h"

void SharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTSharedValueAssignmentStatementNode> sharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(sharedValueAssignmentStatement->getExpression(), context, scope);
    sharedValueAssignmentStatement->getVariableAssignment()->setTypeSignature(
            scope->find(
                    sharedValueAssignmentStatement
                            ->getVariableAssignment()
                            ->getIdentifierNode()
                            ->getId()
            )
    );
}