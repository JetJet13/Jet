//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../../../../ir-type/ir-function-type.h"

class FunctionTypeSignatureIRStrategy {
public:
    IRFunctionType* generate(FunctionTypeSignature* functionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_IR_STRATEGY_H
