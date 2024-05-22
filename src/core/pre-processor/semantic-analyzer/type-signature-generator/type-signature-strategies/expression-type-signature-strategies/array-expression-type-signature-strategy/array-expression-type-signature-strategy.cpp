//
// Created by Johny Georges on 2024-05-07.
//

#include "array-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ArrayExpressionTypeSignatureStrategy::assign(ASTArrayExpressionNode* arrayExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    if (arrayExpression->size() == 0) {
        arrayExpression->setTypeSignature(new ArrayTypeSignature(new InvalidTypeSignature()));
        return;
    }

    for (auto element : *arrayExpression->getElements()) {
        strategyMap->assignTypeSignatureForExpression(element, scope);
    }


    arrayExpression->setTypeSignature(new ArrayTypeSignature(arrayExpression->getElements()->at(0)->getTypeSignature()));
}