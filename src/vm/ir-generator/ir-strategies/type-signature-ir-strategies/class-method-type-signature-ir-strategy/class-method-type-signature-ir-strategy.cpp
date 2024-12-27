//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-type-signature-ir-strategy.h"

IRFunctionType* ClassMethodTypeSignatureIRStrategy::generate(ClassMethodTypeSignature* classMethodTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(classMethodTypeSignature->getReturnType());
    auto parameterTypes = irGenerator->generateParameterList(classMethodTypeSignature->getParameters());
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}