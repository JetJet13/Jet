//
// Created by Johny Georges on 2024-05-23.
//

#include "class-property-assignment-statement-type-signature-strategy.h"

void ClassPropertyAssignmentStatementTypeSignatureStrategy::assign(ASTClassPropertyAssignmentStatementNode* classPropertyAssignmentStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(classPropertyAssignmentStatementNode->getExpression(), scope);
    classPropertyAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(
        scope->find(
            classPropertyAssignmentStatementNode
            ->getPropertyAssignment()
            ->getProperty()
            ->getId()
        )
    );
}