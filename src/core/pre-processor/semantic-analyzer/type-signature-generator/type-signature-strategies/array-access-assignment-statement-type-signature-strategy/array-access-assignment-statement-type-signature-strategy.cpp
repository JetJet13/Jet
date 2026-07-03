//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-type-signature-strategy.h"

void ArrayAccessAssignmentStatementTypeSignatureStrategy::assign(ASTArrayAccessAssignmentStatementNode* arrayAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessAssignmentStatement->getArrayAccessAssignment()->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessAssignmentStatement->getExpression(), context, scope);
}