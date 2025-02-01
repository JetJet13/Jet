//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-signature-strategy.h"

void DrefExpressionTypeSignatureStrategy::assign(ASTDrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    node->setTypeSignature(node->getExpressionNode()->getTypeSignature());
}