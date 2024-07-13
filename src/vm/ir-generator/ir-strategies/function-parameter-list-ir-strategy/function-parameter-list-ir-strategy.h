//
// Created by Johny Georges on 2024-07-09.
//

#ifndef JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H
#define JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../ir-lookup-table/ir-lookup-table.h"

class FunctionParameterListIRStrategy {
public:
    IRFunctionParameterListNode* generate(ASTFunctionParameterListNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, llvm::Function* irFunction);
};

#endif //JETLANG_FUNCTION_PARAMETER_LIST_IR_STRATEGY_H
