//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-type-signature-strategy.h"

void TupleAccessAssignmentStatementTypeSignatureStrategy::assign(ASTTupleAccessAssignmentStatementNode* objectAccessAssignmentStatement, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getExpression(), context, scope);
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getTupleAccessAssignment()->getTupleAccess(), context, scope);
}