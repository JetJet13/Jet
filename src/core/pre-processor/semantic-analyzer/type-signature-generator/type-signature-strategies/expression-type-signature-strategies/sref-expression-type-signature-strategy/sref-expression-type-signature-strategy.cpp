//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-type-signature-strategy.h"

void SrefExpressionTypeSignatureStrategy::assign(ASTSrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->typeSourceIs(POINTER_TYPE_SOURCE)) {
        node->setTypeSignature(node->getExpressionNode()->getTypeSignature());
    } else {
        node->setTypeSignature(new UnknownTypeSignature());
    }
}