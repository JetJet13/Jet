//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), scope);
    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto functionTypeSignature = (InvocableTypeSignature*)structSource->getTypeSignatureForKey(id);
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    } else if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto id = FunctionIdGenerator::generateFor(objectAccessInvocationExpression);
        auto classInstanceSource = (ClassInstanceTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        auto classMethodTypeSignature = classInstanceSource->findMethod(id).value_or(new ClassMethodTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(classMethodTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(classMethodTypeSignature->getReturnType());
        return;
    } else if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto arrayPrototypeTypeSignature = strategyMap->findArrayPrototypeTypeSignature(id, arraySource->getElementType()).value_or(new FunctionTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(arrayPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(arrayPrototypeTypeSignature->getReturnType());
        return;
    } else if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refSource = (RefTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        auto id = objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId();
        auto refPrototypeTypeSignature = strategyMap->findRefPrototypeTypeSignature(id, refSource->getUnderlyingType()).value_or(new FunctionTypeSignature());
        objectAccessInvocationExpression->getObjectAccess()->setTypeSignature(refPrototypeTypeSignature);
        objectAccessInvocationExpression->setTypeSignature(refPrototypeTypeSignature->getReturnType());
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(new InvalidTypeSignature());
}
