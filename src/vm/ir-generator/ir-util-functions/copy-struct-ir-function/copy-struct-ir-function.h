//
// Created by Johny Georges on 2025-04-16.
//

#ifndef JETLANG_COPY_STRUCT_IR_FUNCTION_H
#define JETLANG_COPY_STRUCT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyStructIRFunction {
public:
    static std::string getCopyStructIRFunctionName();
    static void declareCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_COPY_STRUCT_IR_FUNCTION_H
