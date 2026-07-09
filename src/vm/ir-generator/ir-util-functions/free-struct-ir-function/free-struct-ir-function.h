//
// Created by Johny Georges on 2025-04-30.
//

#ifndef JETLANG_FREE_STRUCT_IR_FUNCTION_H
#define JETLANG_FREE_STRUCT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeStructIRFunction {
public:
    static std::string getFreeStructIRFunctionName();
    static void declareFreeStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateFreeStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_FREE_STRUCT_IR_FUNCTION_H
