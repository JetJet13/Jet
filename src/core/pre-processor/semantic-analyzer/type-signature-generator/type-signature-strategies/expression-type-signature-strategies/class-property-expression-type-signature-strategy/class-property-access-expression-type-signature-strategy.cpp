//
// Created by Johny Georges on 2024-05-07.
//

#include "class-property-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"

TypeSignature* ClassPropertyAccessExpressionTypeSignatureStrategy::create(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto classPropertyTypeSignature = typeSignatureLookupTable->find(classPropertyAccessExpression->getId());
    if (!classPropertyTypeSignature->is(CLASS_PROPERTY_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    return ((ClassPropertyTypeSignature*)classPropertyTypeSignature)->getType();
}