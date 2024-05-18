//
// Created by Johny Georges on 2024-05-09.
//

#include "array-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/array-type-signature/array-type-signature.h"

TypeSignature* ArrayTypeTypeSignatureStrategy::create(ASTArrayTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return new ArrayTypeSignature(strategyMap->getTypeSignatureForType(node->getElementType(), scope));
}