//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-shared-value-assignment-statement-type-signature-strategy.h"

void ArrayAccessSharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> arrayAccessSharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessSharedValueAssignmentStatement->getArrayAccessAssignment()->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessSharedValueAssignmentStatement->getExpression(), context, scope);
}