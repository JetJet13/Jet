//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getArguments(), scope);
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getObjectAccess(), scope);
    auto id = FunctionIdGenerator::generateFor(objectAccessInvocationExpression);
    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        objectAccessInvocationExpression->setTypeSignature(structSource->getTypeSignatureForKey(
                objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        )->getTargetTypeSignature());
        return;
    } else if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstanceSource = (ClassInstanceTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        objectAccessInvocationExpression->setTypeSignature(
                classInstanceSource->findMethod(id)
                .value_or(new ClassMethodTypeSignature())->getReturnType());
        return;
    } else if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        objectAccessInvocationExpression->setTypeSignature(strategyMap->findArrayPrototypeTypeSignature(
                objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                arraySource->getElementType()
        ).value_or(new FunctionTypeSignature())->getReturnType());
        return;
    }
    objectAccessInvocationExpression->setTypeSignature(new InvalidTypeSignature());
}
