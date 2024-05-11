//
// Created by Johny Georges on 2024-05-09.
//

#include "this-type-type-signature-strategy.h"

TypeSignature* ThisTypeTypeSignatureStrategy::create(ASTThisTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    return typeSignatureLookupTable->find(node->getId());
}