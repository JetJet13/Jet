//
// Created by Johny Georges on 2024-05-07.
//

#include "class-property-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/class-type-signature/class-type-signature.h"

void ClassPropertyAccessExpressionTypeSignatureStrategy::assign(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeSignatureLookupTable* scope) {
    auto classTypeSignature = (ClassTypeSignature*)scope->find(classPropertyAccessExpression->getPropertyAccess()->getClassAccess()->getThis()->getId());
    auto classPropertyTypeSignature = classTypeSignature->getInstanceProperties()->find(classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
    if (!classPropertyTypeSignature) {
        auto classMethodTypeSignature = classTypeSignature->getMethods()->find(classPropertyAccessExpression->getPropertyAccess()->getPropertyName()->getId());
        if (!classMethodTypeSignature) {
            classPropertyAccessExpression->setTypeSignature(new InvalidTypeSignature());
            return;
        }

        classPropertyAccessExpression->setTypeSignature(classMethodTypeSignature.value());
        return;
    }
    classPropertyAccessExpression->setTypeSignature(classPropertyTypeSignature.value()->getType());
}