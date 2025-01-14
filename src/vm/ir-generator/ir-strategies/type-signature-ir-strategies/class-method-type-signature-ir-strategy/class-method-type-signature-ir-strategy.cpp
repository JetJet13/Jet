//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-type-signature-ir-strategy.h"

IRFunctionType* ClassMethodTypeSignatureIRStrategy::generate(ClassMethodTypeSignature* classMethodTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(classMethodTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(classMethodTypeSignature->getParameters(), scope, irContext);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}