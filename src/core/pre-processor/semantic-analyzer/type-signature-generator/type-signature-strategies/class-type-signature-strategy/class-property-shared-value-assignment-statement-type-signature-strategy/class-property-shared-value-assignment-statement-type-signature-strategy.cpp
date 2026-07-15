//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-shared-value-assignment-statement-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void ClassPropertySharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> classPropertySharedValueAssignmentStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classPropertySharedValueAssignmentStatementNode->getExpression(), context, scope);
    auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(scope->find(
            classPropertySharedValueAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getClassAccess()
                    ->getThis()
                    ->getId()
    ));

    if (!classTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        classPropertySharedValueAssignmentStatementNode
                ->getPropertyAssignment()
                ->setTypeSignature(std::make_shared<InvalidTypeSignature>());
    }

    auto propertyTypeSignature = classTypeSignature->getInstanceProperties()->find(
            classPropertySharedValueAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getProperty()
                    ->getId()
    );
    if (propertyTypeSignature) {
        classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(propertyTypeSignature.value()->getType());
        return;
    }
    classPropertySharedValueAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(
            std::make_shared<InvalidTypeSignature>()
    );
}