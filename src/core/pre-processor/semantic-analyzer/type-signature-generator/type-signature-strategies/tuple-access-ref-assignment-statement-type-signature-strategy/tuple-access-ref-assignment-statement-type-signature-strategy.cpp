//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-ref-assignment-statement-type-signature-strategy.h"

void TupleAccessRefAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> tupleAccessRefAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessRefAssignmentStatement->getExpression(), context, scope);
    tupleAccessRefAssignmentStatement->getExpression()->setTypeSignature(
            tupleAccessRefAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(tupleAccessRefAssignmentStatement->getTupleAccessAssignment()->getTupleAccess(), context, scope);
}