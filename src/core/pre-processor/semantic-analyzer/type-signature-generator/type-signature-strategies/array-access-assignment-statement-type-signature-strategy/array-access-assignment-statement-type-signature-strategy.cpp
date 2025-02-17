//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-type-signature-strategy.h"

void ArrayAccessAssignmentStatementTypeSignatureStrategy::assign(ASTArrayAccessAssignmentStatementNode* arrayAccessAssignmentStatement, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessAssignmentStatement->getExpression(), scope);
    strategyMap->assignTypeSignatureFor(arrayAccessAssignmentStatement->getArrayAccessAssignment()->getArrayAccess(), scope);
}