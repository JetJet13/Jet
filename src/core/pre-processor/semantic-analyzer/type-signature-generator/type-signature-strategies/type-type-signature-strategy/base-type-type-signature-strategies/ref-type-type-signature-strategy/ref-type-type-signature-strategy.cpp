//
// Created by Johny Georges on 2025-02-08.
//

#include "ref-type-type-signature-strategy.h"
#include "../../../../../../../../shared/utils/logger/logger.h"

void RefTypeTypeSignatureStrategy::assign(ASTRefTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getRefType(), scope);
    node->setTypeSignature(new PointerTypeSignature(node->getRefType()->getTypeSignature()));
}