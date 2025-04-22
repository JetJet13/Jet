//
// Created by Johny Georges on 2025-04-05.
//

#ifndef JETLANG_COPY_ARRAY_IR_FUNCTION_H
#define JETLANG_COPY_ARRAY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyArrayIRFunction {
public:
    static std::string getCopyArrayIRFunctionName();
    static void declareCopyArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateCopyArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_COPY_ARRAY_IR_FUNCTION_H
