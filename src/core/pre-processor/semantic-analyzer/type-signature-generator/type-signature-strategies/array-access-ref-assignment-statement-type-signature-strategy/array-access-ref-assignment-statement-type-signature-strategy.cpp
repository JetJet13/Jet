//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-ref-assignment-statement-type-signature-strategy.h"

void ArrayAccessRefAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayAccessRefAssignmentStatementNode> arrayAccessRefAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessRefAssignmentStatement->getArrayAccessAssignment()->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessRefAssignmentStatement->getExpression(), context, scope);
}