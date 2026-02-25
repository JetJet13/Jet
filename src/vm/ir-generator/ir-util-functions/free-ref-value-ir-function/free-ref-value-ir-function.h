//
// Created by Johny Georges on 2026-02-24.
//

#ifndef JETLANG_FREE_REF_VALUE_IR_FUNCTION_H
#define JETLANG_FREE_REF_VALUE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeRefValueIRFunction {
public:
    static std::string getFreeRefValueIRFunctionName();
    static void generateFreeRefValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_FREE_REF_VALUE_IR_FUNCTION_H
