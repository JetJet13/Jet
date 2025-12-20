//
// Created by Johny Georges on 2025-12-19.
//

#ifndef JETLANG_FREE_STRUCT_REF_IR_FUNCTION_H
#define JETLANG_FREE_STRUCT_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeStructRefIRFunction {
public:
    static std::string getFreeStructRefIRFunctionName();
    static void declareFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_FREE_STRUCT_REF_IR_FUNCTION_H
