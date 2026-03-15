//
// Created by Johny Georges on 2024-05-11.
//

#include "object-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void ObjectAccessExpressionTypeSignatureStrategy::assign(ASTObjectAccessExpressionNode* objectAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessExpression->getSource()->getSource(), scope);
    auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        sourceTypeSignature = ((RefTypeSignature*)sourceTypeSignature)->getUnderlyingType();
    }

    if (sourceTypeSignature->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)sourceTypeSignature;
        objectAccessExpression->setTypeSignature(structSource->getTypeSignatureForKey(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (sourceTypeSignature->typeTargetIs(ENUM_TYPE_SOURCE)) {
        auto enumSource = (EnumTypeSignature*)sourceTypeSignature;
        objectAccessExpression->setTypeSignature(new EnumAccessTypeSignature(
            enumSource,
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (sourceTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)sourceTypeSignature;
        objectAccessExpression->setTypeSignature(strategyMap->findArrayPrototypeTypeSignature(
                objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                arraySource->getElementType()).value_or(new FunctionTypeSignature())
        );
        return;
    } else if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstanceSource = (ClassInstanceTypeSignature*)sourceTypeSignature;
        auto id = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto classProperty = classInstanceSource->getKeyValuePairs()->find(id);
        if (classProperty) {
            objectAccessExpression->setTypeSignature(classProperty.value());
            return;
        }
    } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
        auto classSource = (ClassTypeSignature*)sourceTypeSignature;
        auto id = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto classStaticProperty = classSource->getInterface()->find(id);
        if (classStaticProperty) {
            objectAccessExpression->setTypeSignature(classStaticProperty.value());
            return;
        }
    } else if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refSource = (RefTypeSignature*)objectAccessExpression->getSource()->getSource()->getTypeSignature();
        auto refPrototypeTypeSignature = strategyMap->findRefPrototypeTypeSignature(
                objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                refSource->getUnderlyingType());
        if (refPrototypeTypeSignature) {
            objectAccessExpression->setTypeSignature(refPrototypeTypeSignature.value());
        }
        return;
    }
    objectAccessExpression->setTypeSignature(new InvalidTypeSignature());
}