//
// Created by Johny Georges on 2024-07-11.
//

#include "function-type-signature-ir-strategy.h"

IRFunctionType* FunctionTypeSignatureIRStrategy::generate(std::shared_ptr<FunctionTypeSignature> functionTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(functionTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(functionTypeSignature->getParameterList(), scope, irContext);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}