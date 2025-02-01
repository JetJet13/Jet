//
// Created by Johny Georges on 2025-02-01.
//

#include "ref-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void RefExpressionTypeSignatureStrategy::assign(ASTRefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    node->setTypeSignature(new PointerTypeSignature(node->getExpressionNode()->getTypeSignature()));
}