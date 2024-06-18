//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

llvm::Type* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, IRGenerator* irGenerator) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType());
    return llvm::ArrayType::get(arrayElementType, 0);
}