//
// Created by Johny Georges on 2024-05-07.
//

#include "array-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void ArrayAccessExpressionTypeSignatureStrategy::assign(ASTArrayAccessExpressionNode* arrayAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getSource(), scope);
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getIndex()->getIndex(), scope);
    if (!arrayAccessExpression->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        arrayAccessExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    if (arrayAccessExpression->getSource()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)arrayAccessExpression->getSource()->getTypeSignature();
        auto arrayTypeSignature = (ArrayTypeSignature*)refTypeSignature->getUnderlyingType();
        arrayAccessExpression->setTypeSignature(arrayTypeSignature->getElementType());
        return;
    }
    arrayAccessExpression->setTypeSignature(((ArrayTypeSignature*)arrayAccessExpression->getSource()->getTypeSignature())->getElementType());
}