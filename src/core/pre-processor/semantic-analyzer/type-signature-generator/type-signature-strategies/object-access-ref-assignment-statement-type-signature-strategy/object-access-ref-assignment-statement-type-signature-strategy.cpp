//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-ref-assignment-statement-type-signature-strategy.h"

void ObjectAccessRefAssignmentStatementTypeSignatureStrategy::assign(ASTObjectAccessRefAssignmentStatementNode* objectAccessRefAssignmentStatement, std::shared_ptr<TypeSignatureContext> context,  std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessRefAssignmentStatement->getExpression(), context, scope);
    objectAccessRefAssignmentStatement->getExpression()->setTypeSignature(
            objectAccessRefAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(objectAccessRefAssignmentStatement->getObjectAccessAssignment()->getObjectAccess(), context, scope);
}