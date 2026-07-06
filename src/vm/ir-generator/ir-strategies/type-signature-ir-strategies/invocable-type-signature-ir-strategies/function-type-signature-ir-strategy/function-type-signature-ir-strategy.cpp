//
// Created by Johny Georges on 2024-07-11.
//

#include "function-type-signature-ir-strategy.h"

std::shared_ptr<IRFunctionType> FunctionTypeSignatureIRStrategy::generate(std::shared_ptr<FunctionTypeSignature> functionTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(functionTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(functionTypeSignature->getParameterList(), scope, irContext);
    return std::make_shared<IRFunctionType>(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}