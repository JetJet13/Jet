//
// Created by Johny Georges on 2024-05-07.
//

#include "array-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ArrayAccessExpressionTypeSignatureStrategy::assign(ASTArrayAccessExpressionNode* arrayAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(arrayAccessExpression->getSource(), scope);
    if (!arrayAccessExpression->getSource()->getTypeSignature()->is(ARRAY_TYPE_SOURCE)) {
        arrayAccessExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    arrayAccessExpression->setTypeSignature(((ArrayTypeSignature*)arrayAccessExpression->getSource()->getTypeSignature())->getElementType());
}