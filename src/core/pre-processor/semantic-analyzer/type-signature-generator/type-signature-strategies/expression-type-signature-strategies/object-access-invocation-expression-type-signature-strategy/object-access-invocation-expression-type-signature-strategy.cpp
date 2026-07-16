//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), context, scope);

    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedSource = std::dynamic_pointer_cast<SharedTypeSignature>(objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto sharedPrototypeTypeSignature = strategyMap->findSharedPtrPrototypeTypeSignature(id, sharedSource->getUnderlyingType());
        if (sharedPrototypeTypeSignature) {
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(sharedPrototypeTypeSignature.value());
            objectAccessInvocationExpression->setTypeSignature(sharedPrototypeTypeSignature.value()->getReturnType());
            return;
        }
    }

    auto sourceTypeSignature = objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (sourceTypeSignature->typeSourceIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = std::dynamic_pointer_cast<StructTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto functionTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(structSource->getTypeSignatureForKey(id));
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto id = objectAccessInvocationExpression->getName();
        auto classInstanceSource = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(sourceTypeSignature);
        auto classMethodTypeSignature = std::dynamic_pointer_cast<LambdaTypeSignature>(classInstanceSource->getKeyValuePairs()->find(id).value_or(std::make_shared<LambdaTypeSignature>()));
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classMethodTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(classMethodTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classSource = std::dynamic_pointer_cast<ClassTypeSignature>(sourceTypeSignature);
        auto id = classSource->addClassNameToKey(objectAccessInvocationExpression->getName());
        auto classStaticMethod = classSource->getStaticMethods()->find(id);
        if (classStaticMethod) {
            auto classStaticMethodTypeSignature = std::dynamic_pointer_cast<ClassMethodTypeSignature>(classStaticMethod.value());
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classStaticMethodTypeSignature);
            objectAccessInvocationExpression->setTypeSignature(classStaticMethodTypeSignature->getReturnType());
            return;
        }
    } else if (sourceTypeSignature->typeSourceIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = std::dynamic_pointer_cast<ArrayTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findArrayPrototypeTypeSignature(id, arraySource->getElementType()).value_or(std::make_shared<FunctionTypeSignature>());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findStringPrototypeTypeSignature(id).value_or(std::make_shared<FunctionTypeSignature>());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
