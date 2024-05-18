//
// Created by Johny Georges on 2024-05-08.
//

#include "type-type-signature-strategy.h"

TypeSignature* TypeTypeSignatureStrategy::create(ASTTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return strategyMap->getTypeSignatureForBaseType(node->getType(), scope);
}