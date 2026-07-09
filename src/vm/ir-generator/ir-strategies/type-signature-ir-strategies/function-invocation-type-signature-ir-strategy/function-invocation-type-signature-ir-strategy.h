//
// Created by Johny Georges on 2024-11-29.
//

#ifndef JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"

class FunctionInvocationTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRType> generate(std::shared_ptr<FunctionInvocationTypeSignature> functionInvocationTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H
