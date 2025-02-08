//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-signature-strategy.h"

void DrefExpressionTypeSignatureStrategy::assign(ASTDrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->typeSourceIs(POINTER_TYPE_SOURCE)) {
        auto pointerTypeSignature = (PointerTypeSignature*)node->getExpressionNode()->getTypeSignature();
        node->setTypeSignature(pointerTypeSignature->getUnderlyingType());
    } else {
        node->setTypeSignature(new UnknownTypeSignature());
    }
}