//
// Created by Johny Georges on 2024-05-08.
//

#include "type-type-signature-strategy.h"

void TypeTypeSignatureStrategy::assign(ASTTypeNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), context, scope);
}