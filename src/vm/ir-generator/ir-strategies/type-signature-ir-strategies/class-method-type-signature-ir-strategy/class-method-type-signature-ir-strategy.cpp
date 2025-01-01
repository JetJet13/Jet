//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-type-signature-ir-strategy.h"

IRFunctionType* ClassMethodTypeSignatureIRStrategy::generate(ClassMethodTypeSignature* classMethodTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(classMethodTypeSignature->getReturnType(), scope);
    auto parameterTypes = irGenerator->generateParameterList(classMethodTypeSignature->getParameters(), scope);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}