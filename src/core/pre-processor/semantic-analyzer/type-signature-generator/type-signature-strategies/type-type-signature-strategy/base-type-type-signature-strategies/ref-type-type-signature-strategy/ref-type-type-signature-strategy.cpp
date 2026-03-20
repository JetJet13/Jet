//
// Created by Johny Georges on 2025-02-08.
//

#include "ref-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void RefTypeTypeSignatureStrategy::assign(ASTRefTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getRefType(), context, scope);
    node->setTypeSignature(new RefTypeSignature(node->getRefType()->getTypeSignature()));
}