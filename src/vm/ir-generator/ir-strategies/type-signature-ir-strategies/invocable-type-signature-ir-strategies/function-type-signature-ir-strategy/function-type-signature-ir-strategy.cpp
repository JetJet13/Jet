//
// Created by Johny Georges on 2024-07-11.
//

#include "function-type-signature-ir-strategy.h"

IRFunctionType* FunctionTypeSignatureIRStrategy::generate(FunctionTypeSignature* functionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(functionTypeSignature->getReturnType(), scope);
    auto parameterTypes = irGenerator->generateParameterList(functionTypeSignature->getParameterList(), scope);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}