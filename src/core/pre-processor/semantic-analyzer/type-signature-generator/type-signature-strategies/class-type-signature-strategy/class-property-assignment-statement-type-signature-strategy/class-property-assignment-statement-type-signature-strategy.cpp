//
// Created by Johny Georges on 2024-05-23.
//

#include "class-property-assignment-statement-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void ClassPropertyAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> classPropertyAssignmentStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classPropertyAssignmentStatementNode->getExpression(), context, scope);
    auto classTypeSignature = (ClassTypeSignature*)scope->find(
            classPropertyAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getClassAccess()
                    ->getThis()
                    ->getId()
    );

    if (!classTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        classPropertyAssignmentStatementNode
        ->getPropertyAssignment()
        ->setTypeSignature(new InvalidTypeSignature());
    }

    auto propertyTypeSignature = classTypeSignature->getInstanceProperties()->find(
            classPropertyAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getProperty()
                    ->getId()
    );
    if (propertyTypeSignature) {
        classPropertyAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(propertyTypeSignature.value()->getType());
        return;
    }
    classPropertyAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(
            new InvalidTypeSignature()
    );
}