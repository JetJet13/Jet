//
// Created by Johny Georges on 2024-07-25.
//

#include "enum-access-type-signature-ir-strategy.h"

IRType* EnumAccessTypeSignatureIRStrategy::generate(EnumAccessTypeSignature* enumAccessTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    return irGenerator->generateTypeFor(enumAccessTypeSignature->getEnum()->getType(), scope);
}