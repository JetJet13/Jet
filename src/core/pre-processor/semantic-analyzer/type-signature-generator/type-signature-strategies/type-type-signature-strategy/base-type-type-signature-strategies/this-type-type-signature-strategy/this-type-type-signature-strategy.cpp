//
// Created by Johny Georges on 2024-05-09.
//

#include "this-type-type-signature-strategy.h"

void ThisTypeTypeSignatureStrategy::assign(ASTThisTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    node->setTypeSignature(typeSignatureLookupTable->find(node->getId()));
}