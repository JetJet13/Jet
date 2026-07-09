//
// Created by Johny Georges on 2025-12-19.
//

#ifndef JETLANG_COPY_STRUCT_REF_IR_FUNCTION_H
#define JETLANG_COPY_STRUCT_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyStructRefIRFunction {
public:
    static std::string getCopyStructRefIRFunctionName();
    static void declareCopyStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateCopyStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};


#endif //JETLANG_COPY_STRUCT_REF_IR_FUNCTION_H
