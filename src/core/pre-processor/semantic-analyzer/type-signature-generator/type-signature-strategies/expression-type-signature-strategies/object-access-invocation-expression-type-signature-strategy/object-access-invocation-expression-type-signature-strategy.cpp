//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), context, scope);

    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(REF_TYPE_SOURCE)) {
        auto refSource = (RefTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto refPrototypeTypeSignature = strategyMap->findRefPrototypeTypeSignature(id, refSource->getUnderlyingType());
        if (refPrototypeTypeSignature) {
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(refPrototypeTypeSignature.value());
            objectAccessInvocationExpression->setTypeSignature(refPrototypeTypeSignature.value()->getReturnType());
            return;
        }
    }

    auto sourceTypeSignature = objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        sourceTypeSignature = ((RefTypeSignature*)sourceTypeSignature)->getUnderlyingType();
    }

    if (sourceTypeSignature->typeSourceIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto functionTypeSignature = (InvocableTypeSignature*)structSource->getTypeSignatureForKey(id);
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto id = objectAccessInvocationExpression->getName();
        auto classInstanceSource = (ClassInstanceTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto classMethodTypeSignature = (ClassMethodTypeSignature*)classInstanceSource->getKeyValuePairs()->find(id).value_or(new ClassMethodTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classMethodTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(classMethodTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classSource = (ClassTypeSignature*)sourceTypeSignature;
        auto id = classSource->addClassNameToKey(objectAccessInvocationExpression->getName());
        auto classStaticMethod = classSource->getStaticMethods()->find(id);
        if (classStaticMethod) {
            auto classStaticMethodTypeSignature = (ClassMethodTypeSignature*)classStaticMethod.value();
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classStaticMethodTypeSignature);
            objectAccessInvocationExpression->setTypeSignature(classStaticMethodTypeSignature->getReturnType());
            return;
        }
    } else if (sourceTypeSignature->typeSourceIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findArrayPrototypeTypeSignature(id, arraySource->getElementType()).value_or(new FunctionTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findStringPrototypeTypeSignature(id).value_or(new FunctionTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(new InvalidTypeSignature());
}
