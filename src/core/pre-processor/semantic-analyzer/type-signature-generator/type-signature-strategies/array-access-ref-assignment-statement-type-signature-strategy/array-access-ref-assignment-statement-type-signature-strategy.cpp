//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-ref-assignment-statement-type-signature-strategy.h"

void ArrayAccessRefAssignmentStatementTypeSignatureStrategy::assign(ASTArrayAccessRefAssignmentStatementNode* arrayAccessRefAssignmentStatement, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessRefAssignmentStatement->getArrayAccessAssignment()->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessRefAssignmentStatement->getExpression(), context, scope);
}