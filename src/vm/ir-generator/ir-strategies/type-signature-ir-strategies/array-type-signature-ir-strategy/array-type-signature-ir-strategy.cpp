//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRArrayType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType());

    return new IRArrayType(
            new IRPointerType(
                llvm::PointerType::get(arrayElementType->getType(), 0),
                arrayElementType
            )
    );
}