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
    std::shared_ptr<IRFunctionType> generate(std::shared_ptr<FunctionTypeSignature> functionTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_IR_STRATEGY_H
