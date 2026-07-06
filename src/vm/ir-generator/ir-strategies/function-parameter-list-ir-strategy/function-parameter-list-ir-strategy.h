//
// Created by Johny Georges on 2024-07-09.
//

#ifndef JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"

class FunctionParameterListIRStrategy {
public:
    std::shared_ptr<IRFunctionParameterListNode> generate(std::shared_ptr<ASTFunctionParameterListNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, llvm::Function* irFunction);
};

#endif //JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H
