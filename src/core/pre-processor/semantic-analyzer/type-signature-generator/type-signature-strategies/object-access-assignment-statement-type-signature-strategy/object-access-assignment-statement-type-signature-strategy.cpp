//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-type-signature-strategy.h"

void ObjectAccessAssignmentStatementTypeSignatureStrategy::assign(ASTObjectAccessAssignmentStatementNode* objectAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context,  std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getExpression(), context, scope);
    objectAccessAssignmentStatement->getExpression()->setTypeSignature(
            objectAccessAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(objectAccessAssignmentStatement->getObjectAccessAssignment()->getObjectAccess(), context, scope);
}