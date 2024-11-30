//
// Created by Johny Georges on 2024-11-29.
//

#ifndef JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"

class FunctionInvocationTypeSignatureIRStrategy {
public:
    IRType* generate(FunctionInvocationTypeSignature* functionInvocationTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_IR_STRATEGY_H
