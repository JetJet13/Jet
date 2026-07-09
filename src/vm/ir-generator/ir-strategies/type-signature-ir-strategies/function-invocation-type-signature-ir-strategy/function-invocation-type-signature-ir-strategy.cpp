//
// Created by Johny Georges on 2024-11-29.
//

#include "function-invocation-type-signature-ir-strategy.h"

std::shared_ptr<IRType> FunctionInvocationTypeSignatureIRStrategy::generate(std::shared_ptr<FunctionInvocationTypeSignature> functionInvocationTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return irGenerator->generateTypeFor(functionInvocationTypeSignature->getReturnType(), scope, irContext);
}