//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-ref-value-assignment-statement-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy::assign(ASTClassPropertyRefValueAssignmentStatementNode* classPropertyRefValueAssignmentStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classPropertyRefValueAssignmentStatementNode->getExpression(), scope);
    auto classTypeSignature = (ClassTypeSignature*)scope->find(
            classPropertyRefValueAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getClassAccess()
                    ->getThis()
                    ->getId()
    );

    if (!classTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        classPropertyRefValueAssignmentStatementNode
                ->getPropertyAssignment()
                ->setTypeSignature(new InvalidTypeSignature());
    }

    auto propertyTypeSignature = classTypeSignature->getProperties()->find(
            classPropertyRefValueAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getProperty()
                    ->getId()
    );
    if (propertyTypeSignature) {
        classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(propertyTypeSignature.value()->getType());
        return;
    }
    classPropertyRefValueAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(
            new InvalidTypeSignature()
    );
}