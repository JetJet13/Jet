//
// Created by Johny Georges on 2025-04-05.
//

#ifndef JETLANG_COPY_POINTER_IR_FUNCTION_H
#define JETLANG_COPY_POINTER_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyPointerIRFunction {
public:
    static std::string getCopyPointerIRFunctionName();
    static void declareCopyPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateCopyPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_COPY_POINTER_IR_FUNCTION_H
