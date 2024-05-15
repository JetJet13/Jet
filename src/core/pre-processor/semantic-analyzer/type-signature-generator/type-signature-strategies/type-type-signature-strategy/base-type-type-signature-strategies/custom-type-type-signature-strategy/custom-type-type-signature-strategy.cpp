//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* CustomTypeTypeSignatureStrategy::create(ASTCustomTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    return typeSignatureLookupTable->find(
                tokenTable->getIdentifier(
                    node
                    ->getIdentifier()
                    ->getIdentifier()
                    ->getToken()
                    ->getValueId()
                    .value()
                ).value()
            );
}