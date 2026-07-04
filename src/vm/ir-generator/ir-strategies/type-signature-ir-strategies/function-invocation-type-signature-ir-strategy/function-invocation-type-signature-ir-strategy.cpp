//
// Created by Johny Georges on 2024-11-29.
//

#include "function-invocation-type-signature-ir-strategy.h"

IRType* FunctionInvocationTypeSignatureIRStrategy::generate(std::shared_ptr<FunctionInvocationTypeSignature> functionInvocationTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return irGenerator->generateTypeFor(functionInvocationTypeSignature->getReturnType(), scope, irContext);
}