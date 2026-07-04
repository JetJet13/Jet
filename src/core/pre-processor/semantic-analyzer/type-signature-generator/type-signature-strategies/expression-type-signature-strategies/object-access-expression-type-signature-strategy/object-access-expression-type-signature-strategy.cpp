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

void ObjectAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessExpression->getSource()->getSource(), context, scope);
    auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<RefTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (sourceTypeSignature->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = std::dynamic_pointer_cast<StructTypeSignature>(sourceTypeSignature);
        objectAccessExpression->setTypeSignature(structSource->getTypeSignatureForKey(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (sourceTypeSignature->typeTargetIs(ENUM_TYPE_SOURCE)) {
        auto enumSource = std::dynamic_pointer_cast<EnumTypeSignature>(sourceTypeSignature);
        objectAccessExpression->setTypeSignature(std::make_shared<EnumAccessTypeSignature>(
            enumSource,
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (sourceTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = std::dynamic_pointer_cast<ArrayTypeSignature>(sourceTypeSignature);
        objectAccessExpression->setTypeSignature(strategyMap->findArrayPrototypeTypeSignature(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
            arraySource->getElementType()).value_or(std::make_shared<FunctionTypeSignature>())
        );
        return;
    } else if (sourceTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)) {
        objectAccessExpression->setTypeSignature(strategyMap->findStringPrototypeTypeSignature(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()).value_or(std::make_shared<FunctionTypeSignature>())
        );
        return;
    } else if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
        auto id = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto classProperty = classInstanceSource->getKeyValuePairs()->find(id);
        if (classProperty) {
            objectAccessExpression->setTypeSignature(classProperty.value()->convertToVariableTypeSignature());
            return;
        }
    } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
        auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
        auto id = classSource->addClassNameToKey(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId());
        auto classStaticProperty = classSource->getStaticProperties()->find(id);
        if (classStaticProperty) {
            objectAccessExpression->setTypeSignature(classStaticProperty.value()->convertToVariableTypeSignature());
            return;
        }
    } else if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refSource = std::dynamic_pointer_cast<RefTypeSignature>(objectAccessExpression->getSource()->getSource()->getTypeSignature());
        auto refPrototypeTypeSignature = strategyMap->findRefPrototypeTypeSignature(
                objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                refSource->getUnderlyingType());
        if (refPrototypeTypeSignature) {
            objectAccessExpression->setTypeSignature(refPrototypeTypeSignature.value());
        }
        return;
    }
    objectAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}