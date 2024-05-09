//
// Created by Johny Georges on 2024-05-07.
//

#include "array-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"

TypeSignature* ArrayExpressionTypeSignatureStrategy::create(ASTArrayExpressionNode* arrayExpression, TypeSignatureStrategyProvider* strategyMap) {
    if (arrayExpression->size() == 0) {
        return new ArrayTypeSignature(new InvalidTypeSignature(), 0);
    }

    TypeSignature* lastElementTypeSignature = strategyMap->getTypeSignatureFor(arrayExpression->getElements()->at(0));
    for (auto element : *arrayExpression->getElements()) {
        auto elementTypeSignature = strategyMap->getTypeSignatureFor(element);
        if (!lastElementTypeSignature->isEqualTo(elementTypeSignature)) {
            return new InvalidTypeSignature();
        }
    }
    return new ArrayTypeSignature(lastElementTypeSignature, arrayExpression->size());
}