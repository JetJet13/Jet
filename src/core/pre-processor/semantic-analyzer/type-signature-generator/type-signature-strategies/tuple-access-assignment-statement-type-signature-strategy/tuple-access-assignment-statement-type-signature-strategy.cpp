//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-type-signature-strategy.h"

void TupleAccessAssignmentStatementTypeSignatureStrategy::assign(ASTTupleAccessAssignmentStatementNode* tupleAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessAssignmentStatement->getExpression(), context, scope);
    tupleAccessAssignmentStatement->getExpression()->setTypeSignature(
            tupleAccessAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(tupleAccessAssignmentStatement->getTupleAccessAssignment()->getTupleAccess(), context, scope);
}