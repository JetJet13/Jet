//
// Created by Johny Georges on 2024-07-25.
//

#include "enum-access-type-signature-ir-strategy.h"

IRPointerType* EnumAccessTypeSignatureIRStrategy::generate(EnumAccessTypeSignature* enumAccessTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    return irGenerator->generateTypeFor(enumAccessTypeSignature->getEnum()->getType());
}