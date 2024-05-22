//
// Created by Johny Georges on 2024-05-08.
//

#include "type-type-signature-strategy.h"

void TypeTypeSignatureStrategy::assign(ASTTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForBaseType(node->getType(), scope);
}