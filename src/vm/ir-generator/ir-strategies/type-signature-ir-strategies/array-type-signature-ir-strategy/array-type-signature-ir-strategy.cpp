//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRArrayPointerType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType(), scope);
    if (arrayElementType->isPointerType()) {
        return irGenerator->generateArrayPointerType((IRPointerType *) arrayElementType);
    }
    return irGenerator->generateArrayPointerType(irGenerator->generateIrPointerType(arrayElementType));
}