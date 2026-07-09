//
// Created by Johny Georges on 2025-12-10.
//

#ifndef JETLANG_COPY_LAMBDA_IR_FUNCTION_H
#define JETLANG_COPY_LAMBDA_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyLambdaIRFunction {
public:
    static std::string getCopyLambdaIRFunctionName();
    static void declareCopyLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateCopyLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_COPY_LAMBDA_IR_FUNCTION_H
