//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"


void CustomTypeTypeSignatureStrategy::assign(ASTCustomTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(node->getId());
    node->setTypeSignature(customTypeSignature);
}