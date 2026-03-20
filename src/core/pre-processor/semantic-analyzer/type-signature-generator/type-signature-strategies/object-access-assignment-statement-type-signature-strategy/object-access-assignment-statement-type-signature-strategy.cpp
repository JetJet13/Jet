//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-type-signature-strategy.h"

void ObjectAccessAssignmentStatementTypeSignatureStrategy::assign(ASTObjectAccessAssignmentStatementNode* objectAccessAssignmentStatement, TypeSignatureContext* context,  TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getExpression(), context, scope);
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getObjectAccessAssignment()->getObjectAccess(), context, scope);
}