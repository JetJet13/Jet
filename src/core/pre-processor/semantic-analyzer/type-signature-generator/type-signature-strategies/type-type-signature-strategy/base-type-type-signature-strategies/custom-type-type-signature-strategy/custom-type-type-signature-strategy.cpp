//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* CustomTypeTypeSignatureStrategy::create(ASTCustomTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    auto customTypeValueId = node->getIdentifier()->getIdentifier()->getToken()->getValueId();
    if (customTypeValueId && tokenTable->getIdentifier(customTypeValueId.value())) {
        return typeSignatureLookupTable->find(tokenTable->getIdentifier(customTypeValueId.value()).value());
    }
    return new InvalidTypeSignature();
}