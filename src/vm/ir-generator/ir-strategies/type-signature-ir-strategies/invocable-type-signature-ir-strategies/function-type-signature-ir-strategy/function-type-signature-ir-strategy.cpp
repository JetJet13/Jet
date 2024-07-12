//
// Created by Johny Georges on 2024-07-11.
//

#include "function-type-signature-ir-strategy.h"

IRType* FunctionTypeSignatureIRStrategy::generate(FunctionTypeSignature* functionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(functionTypeSignature->getReturnType());
    auto parameterTypes = irGenerator->generateTypeFor(functionTypeSignature->getParameterList());
    return new IRType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getType(), false));
}