//
// Created by Johny Georges on 2025-07-12.
//

#include "void-type-type-signature-strategy.h"

void VoidTypeTypeSignatureStrategy::assign(ASTVoidTypeNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    node->setTypeSignature(new VoidTypeSignature());
}