//
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature-ir-strategy.h"

IRPointerType* PointerTypeSignatureIRStrategy::generate(PointerTypeSignature* pointerTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return IRPointerType::create(irGenerator->generateTypeFor(pointerTypeSignature->getUnderlyingType(), scope, irContext));
}