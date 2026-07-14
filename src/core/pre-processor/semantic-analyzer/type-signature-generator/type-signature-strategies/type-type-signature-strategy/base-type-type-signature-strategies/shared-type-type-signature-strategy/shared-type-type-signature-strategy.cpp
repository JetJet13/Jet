//
// Created by Johny Georges on 2026-07-11.
//

#include "shared-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void SharedTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTSharedTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getSharedType(), context, scope);
    node->setTypeSignature(std::make_shared<SharedTypeSignature>(node->getSharedType()->getTypeSignature()->convertToVariableTypeSignature()));
}