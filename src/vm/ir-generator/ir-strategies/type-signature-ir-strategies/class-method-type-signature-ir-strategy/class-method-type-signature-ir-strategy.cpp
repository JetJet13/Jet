//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-type-signature-ir-strategy.h"

std::shared_ptr<IRFunctionType> ClassMethodTypeSignatureIRStrategy::generate(std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(classMethodTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(classMethodTypeSignature->getParameters(), scope, irContext);
    return std::make_shared<IRFunctionType>(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}