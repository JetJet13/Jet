//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void DrefExpressionTypeSignatureStrategy::assign(ASTDrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)node->getExpressionNode()->getTypeSignature();
        node->setTypeSignature(refTypeSignature->getUnderlyingType());
    } else {
        node->setTypeSignature(new UnknownTypeSignature());
    }
}