//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRArrayPointerType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType(), scope, irContext);
    if (arrayElementType->isPointerType()) {
        return irGenerator->generateArrayPointerType((IRPointerType *) arrayElementType);
    }
    return irGenerator->generateArrayPointerType(irGenerator->generateIrPointerType(arrayElementType));
}
