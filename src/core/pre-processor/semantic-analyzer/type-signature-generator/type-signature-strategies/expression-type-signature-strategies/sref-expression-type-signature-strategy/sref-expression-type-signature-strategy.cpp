//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void SrefExpressionTypeSignatureStrategy::assign(ASTSrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        node->setTypeSignature((RefTypeSignature*)node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature());
    } else {
        node->setTypeSignature(new RefTypeSignature());
    }
}