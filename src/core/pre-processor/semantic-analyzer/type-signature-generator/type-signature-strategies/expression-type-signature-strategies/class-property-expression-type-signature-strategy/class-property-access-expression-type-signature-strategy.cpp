//
// Created by Johny Georges on 2024-05-07.
//

#include "class-property-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"

void ClassPropertyAccessExpressionTypeSignatureStrategy::assign(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto classPropertyTypeSignature = typeSignatureLookupTable->find(classPropertyAccessExpression->getId());
    if (!classPropertyTypeSignature->typeTargetIs(CLASS_PROPERTY_TYPE_SOURCE)) {
        classPropertyAccessExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    classPropertyAccessExpression->setTypeSignature(((ClassPropertyTypeSignature*)classPropertyTypeSignature)->getType());
}