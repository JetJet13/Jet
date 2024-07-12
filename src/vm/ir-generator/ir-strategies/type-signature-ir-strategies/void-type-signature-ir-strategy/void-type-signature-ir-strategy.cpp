//
// Created by Johny Georges on 2024-07-12.
//

#include "void-type-signature-ir-strategy.h"

IRType* VoidTypeSignatureIRStrategy::generate(std::unique_ptr<llvm::LLVMContext>* context) {
    return new IRType(llvm::Type::getVoidTy(**context));
}