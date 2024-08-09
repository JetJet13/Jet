//
// Created by Johny Georges on 2024-08-08.
//

#ifndef JETLANG_COPY_ARRAY_SUPPORT_FUNCTION_IR_STRATEGY_H
#define JETLANG_COPY_ARRAY_SUPPORT_FUNCTION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-module-node.h"

class CopyArraySupportFunctionIRStrategy {
public:
    void generate(std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};


#endif //JETLANG_COPY_ARRAY_SUPPORT_FUNCTION_IR_STRATEGY_H
