//
// Created by Johny Georges on 2025-05-14.
//

#ifndef JETLANG_FREE_REF_IR_FUNCTION_H
#define JETLANG_FREE_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeRefIRFunction {
public:
    static std::string getFreeRefIRFunctionName();
    static void declareFreeRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateFreeRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_FREE_REF_IR_FUNCTION_H
