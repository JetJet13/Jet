//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRArrayPointerType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType());
    if (arrayElementType->isPointerType()) {
        return irGenerator->generateArrayElementType((IRPointerType*)arrayElementType);
    }
    return irGenerator->generateArrayElementType(irGenerator->generatePointerType(arrayElementType));
}