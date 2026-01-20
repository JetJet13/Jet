//
// Created by Johny Georges on 2025-05-14.
//

#ifndef JETLANG_COPY_REF_IR_FUNCTION_H
#define JETLANG_COPY_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyRefIRFunction {
public:
    static std::string getCopyRefIRFunctionName();
    static void declareCopyRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateCopyRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_COPY_REF_IR_FUNCTION_H
