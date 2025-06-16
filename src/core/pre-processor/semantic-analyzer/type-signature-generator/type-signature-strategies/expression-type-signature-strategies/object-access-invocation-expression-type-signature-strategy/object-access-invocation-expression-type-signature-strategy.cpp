//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ObjectAccessInvocationExpressionTypeSignatureStrategy::assign(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessInvocationExpression->getSource()->getSource(), scope);
    if (objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)objectAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        objectAccessInvocationExpression->setTypeSignature(structSource->getTypeSignatureForKey(
                objectAccessInvocationExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
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
