//
// Created by Johny Georges on 2024-07-25.
//

#include "enum-access-type-signature-ir-strategy.h"

IRType* EnumAccessTypeSignatureIRStrategy::generate(EnumAccessTypeSignature* enumAccessTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return irGenerator->generateTypeFor(enumAccessTypeSignature->getEnum()->getType(), scope, irContext);
}