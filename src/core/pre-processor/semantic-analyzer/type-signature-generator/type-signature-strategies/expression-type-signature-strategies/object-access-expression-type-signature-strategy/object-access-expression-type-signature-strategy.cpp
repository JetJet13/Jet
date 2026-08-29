//
// Created by Johny Georges on 2024-05-11.
//

#include "object-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

void ObjectAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessExpression->getSource()->getSource(), context, scope);
    auto sourceTypeSignature = objectAccessExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
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

        if (context->getTypeSignature() && context->getTypeSignature().value()->isInvocable()) {
            auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(context->getTypeSignature().value());
            auto methodId = classInstanceSource->getClass()->addClassNameToKey(FunctionIdGenerator::generateFor(id, invocableTypeSignature));
            auto methodTypeSignature = classInstanceSource->getClass()->getInstanceMethods()->find(methodId);
            if (methodTypeSignature) {
                objectAccessExpression->setTypeSignature(methodTypeSignature.value()->convertToVariableTypeSignature());
                return;
            }
        }

        auto methodTypeSignatureMap = classInstanceSource->getClass()->findInstanceMethodsByName(id);
        // if there is only 1 method type signature for the name provided, then use it
        if (methodTypeSignatureMap && methodTypeSignatureMap.value()->size() == 1) {
            objectAccessExpression->setTypeSignature(methodTypeSignatureMap.value()->begin()->second->convertToVariableTypeSignature());
            return;
        }

    } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
        auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
        auto id = objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto classStaticProperty = classSource->getStaticProperties()->find(classSource->addClassNameToKey(id));
        if (classStaticProperty) {
            objectAccessExpression->setTypeSignature(classStaticProperty.value()->convertToVariableTypeSignature());
            return;
        }

        if (context->getTypeSignature() && context->getTypeSignature().value()->isInvocable()) {
            auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(context->getTypeSignature().value());
            auto methodId = classSource->addClassNameToKey(FunctionIdGenerator::generateFor(id, invocableTypeSignature));
            auto methodTypeSignature = classSource->getStaticMethods()->find(methodId);
            if (methodTypeSignature) {
                objectAccessExpression->setTypeSignature(methodTypeSignature.value()->convertToVariableTypeSignature());
                return;
            }
        }

        auto methodTypeSignatureMap = classSource->findStaticMethodsByName(id);
        // if there is only 1 method type signature for the name provided, then use it
        if (methodTypeSignatureMap && methodTypeSignatureMap.value()->size() == 1) {
            objectAccessExpression->setTypeSignature(methodTypeSignatureMap.value()->begin()->second->convertToVariableTypeSignature());
            return;
        }
    } else if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
        auto sharedSource = std::dynamic_pointer_cast<SharedTypeSignature>(objectAccessExpression->getSource()->getSource()->getTypeSignature());
        auto sharedPrototypeTypeSignature = strategyMap->findSharedPtrPrototypeTypeSignature(
                objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                sharedSource->getUnderlyingType());
        if (sharedPrototypeTypeSignature) {
            objectAccessExpression->setTypeSignature(sharedPrototypeTypeSignature.value());
            return;
        }
    }
    objectAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}