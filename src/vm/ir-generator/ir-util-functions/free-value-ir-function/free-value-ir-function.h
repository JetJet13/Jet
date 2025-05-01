//
// Created by Johny Georges on 2025-04-30.
//

#ifndef JETLANG_FREE_VALUE_IR_FUNCTION_H
#define JETLANG_FREE_VALUE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeValueIRFunction {
public:
    static std::string getFreeValueIRFunctionName();
    static void declareFreeValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_FREE_VALUE_IR_FUNCTION_H
