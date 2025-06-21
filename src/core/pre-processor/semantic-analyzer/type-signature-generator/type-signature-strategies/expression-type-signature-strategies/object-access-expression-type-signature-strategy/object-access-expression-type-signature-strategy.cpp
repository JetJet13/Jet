//
// Created by Johny Georges on 2024-05-11.
//

#include "object-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ObjectAccessExpressionTypeSignatureStrategy::assign(ASTObjectAccessExpressionNode* objectAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(objectAccessExpression->getSource()->getSource(), scope);
    if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)objectAccessExpression->getSource()->getSource()->getTypeSignature();
        objectAccessExpression->setTypeSignature(structSource->getTypeSignatureForKey(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(ENUM_TYPE_SOURCE)) {
        auto enumSource = (EnumTypeSignature*)objectAccessExpression->getSource()->getSource()->getTypeSignature();
        objectAccessExpression->setTypeSignature(new EnumAccessTypeSignature(
            enumSource,
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        ));
        return;
    } else if (objectAccessExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arraySource = (ArrayTypeSignature*)objectAccessExpression->getSource()->getSource()->getTypeSignature();
        objectAccessExpression->setTypeSignature(strategyMap->findArrayPrototypeTypeSignature(
                objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId(),
                arraySource->getElementType()).value_or(new FunctionTypeSignature())
        );
        return;
    }
    objectAccessExpression->setTypeSignature(new InvalidTypeSignature());
}