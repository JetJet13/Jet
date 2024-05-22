//
// Created by Johny Georges on 2024-05-09.
//

#include "custom-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"


void CustomTypeTypeSignatureStrategy::assign(ASTCustomTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(node->getId());
    if (customTypeSignature->is(CLASS_TYPE_SOURCE)) {
        node->setTypeSignature(new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature));
        return;
    }

    node->setTypeSignature(customTypeSignature);
}