//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

TypeSignature* CustomTypeTypeSignatureStrategy::create(ASTCustomTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(
                tokenTable->getIdentifier(
                    node
                    ->getIdentifier()
                    ->getIdentifier()
                    ->getToken()
                    ->getValueId()
                    .value()
                ).value()
            );

    if (customTypeSignature->is(CLASS_TYPE_SOURCE)) {
        return new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature);
    }

    return customTypeSignature;
}