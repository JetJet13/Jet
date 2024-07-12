//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"

IRType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType());
    auto numElementsType = llvm::IntegerType::get(**context, 32);
    auto pointerType = llvm::PointerType::get(arrayElementType->getType(), 0);
    auto arrayAsStructType = llvm::StructType::get(**context, { arrayElementType->getType(), numElementsType, pointerType });
    return new IRType(arrayAsStructType);
}