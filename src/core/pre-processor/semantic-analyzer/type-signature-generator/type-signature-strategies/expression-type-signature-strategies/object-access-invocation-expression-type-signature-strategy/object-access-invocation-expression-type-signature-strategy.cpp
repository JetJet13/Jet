//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), scope);

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

    auto sourceTypeSignature = objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        sourceTypeSignature = ((RefTypeSignature*)sourceTypeSignature)->getUnderlyingType();
    }

    if (sourceTypeSignature->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto functionTypeSignature = (InvocableTypeSignature*)structSource->getTypeSignatureForKey(id);
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto id = FunctionIdGenerator::generateFor(objectAccessInvocationExpression);
        auto classInstanceSource = (ClassInstanceTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto classMethodTypeSignature = (ClassMethodTypeSignature*)classInstanceSource->getKeyValuePairs()->find(id).value_or(new ClassMethodTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classMethodTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(classMethodTypeSignature->getReturnType());
        return;
    } else if (sourceTypeSignature->typeTargetIs(CLASS_TYPE_SOURCE)) {
        auto classSource = (ClassTypeSignature*)sourceTypeSignature;
        auto id = FunctionIdGenerator::generateFor(objectAccessInvocationExpression);
        auto classStaticMethod = classSource->getInterface()->find(id);
        if (classStaticMethod) {
            auto classStaticMethodTypeSignature = (ClassMethodTypeSignature*)classStaticMethod.value();
            objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classStaticMethodTypeSignature);
            objectAccessInvocationExpression->setTypeSignature(classStaticMethodTypeSignature->getReturnType());
            return;
        }
    } else if (sourceTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)sourceTypeSignature->getTargetTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findArrayPrototypeTypeSignature(id, arraySource->getElementType()).value_or(new FunctionTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(new InvalidTypeSignature());
}
