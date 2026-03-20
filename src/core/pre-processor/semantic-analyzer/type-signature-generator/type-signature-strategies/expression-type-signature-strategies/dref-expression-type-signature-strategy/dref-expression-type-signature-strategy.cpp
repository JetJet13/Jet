//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void DrefExpressionTypeSignatureStrategy::assign(ASTDrefExpressionNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature()->typeSourceIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature();
        node->setTypeSignature(refTypeSignature->getUnderlyingType());
    } else {
        node->setTypeSignature(new UnknownTypeSignature());
    }
}