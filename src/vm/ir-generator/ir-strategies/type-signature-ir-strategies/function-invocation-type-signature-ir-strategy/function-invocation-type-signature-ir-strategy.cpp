//
// Created by Johny Georges on 2024-11-29.
//

#include "function-invocation-type-signature-ir-strategy.h"

IRType* FunctionInvocationTypeSignatureIRStrategy::generate(FunctionInvocationTypeSignature* functionInvocationTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    return irGenerator->generateTypeFor(functionInvocationTypeSignature->getReturnType());
}