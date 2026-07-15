//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-shared-value-assignment-statement-type-signature-strategy.h"

void ObjectAccessSharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> objectAccessSharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context,  std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessSharedValueAssignmentStatement->getExpression(), context, scope);
    objectAccessSharedValueAssignmentStatement->getExpression()->setTypeSignature(
            objectAccessSharedValueAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(objectAccessSharedValueAssignmentStatement->getObjectAccessAssignment()->getObjectAccess(), context, scope);
}