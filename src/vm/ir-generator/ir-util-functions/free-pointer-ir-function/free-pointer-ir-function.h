//
// Created by Johny Georges on 2025-04-30.
//

#ifndef JETLANG_FREE_POINTER_IR_FUNCTION_H
#define JETLANG_FREE_POINTER_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreePointerIRFunction {
public:
    static std::string getFreePointerIRFunctionName();
    static void declareFreePointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateFreePointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_FREE_POINTER_IR_FUNCTION_H
