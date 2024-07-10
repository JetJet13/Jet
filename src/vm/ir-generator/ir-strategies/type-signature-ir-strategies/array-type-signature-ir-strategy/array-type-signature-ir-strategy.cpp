//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, IRGenerator* irGenerator) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType());
    return new IRType(llvm::PointerType::get(arrayElementType->getType(), 0));
}