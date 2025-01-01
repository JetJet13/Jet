//
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature-ir-strategy.h"

IRPointerType* PointerTypeSignatureIRStrategy::generate(PointerTypeSignature* pointerTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    return IRPointerType::create(irGenerator->generateTypeFor(pointerTypeSignature->getUnderlyingType(), scope));
}