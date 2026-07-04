//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"

void CustomTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTCustomTypeNode> node, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(node->getId());
    customTypeSignature->setId(node->getId());
    node->setTypeSignature(customTypeSignature);
}