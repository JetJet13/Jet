//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-shared-value-assignment-statement-type-signature-strategy.h"

void TupleAccessSharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> tupleAccessSharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessSharedValueAssignmentStatement->getExpression(), context, scope);
    tupleAccessSharedValueAssignmentStatement->getExpression()->setTypeSignature(
            tupleAccessSharedValueAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(tupleAccessSharedValueAssignmentStatement->getTupleAccessAssignment()->getTupleAccess(), context, scope);
}