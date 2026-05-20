//
// Created by Johny Georges on 2024-05-07.
//

#include "array-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ArrayExpressionTypeSignatureStrategy::assign(ASTArrayExpressionNode* arrayExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    if (arrayExpression->size() == 0 &&
        arrayExpression->getParentNode() &&
        arrayExpression->getParentNode().value()->getTypeSignature()->typeSourceIs(ARRAY_TYPE_SOURCE)) {
        arrayExpression->setTypeSignature(
            (ArrayTypeSignature*)arrayExpression->getParentNode().value()->getTypeSignature()
        );
        return;
    } else if (arrayExpression->size() == 0) {
        return;
    }

    for (auto element : *arrayExpression->getElements()) {
        strategyMap->assignTypeSignatureFor(element, context, scope);
    }

    arrayExpression->setTypeSignature(new ArrayTypeSignature(arrayExpression->getElements()->at(0)->getTypeSignature()->convertToVariableTypeSignature()));
}