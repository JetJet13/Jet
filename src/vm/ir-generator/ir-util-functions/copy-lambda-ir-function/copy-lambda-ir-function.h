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
    static void declareCopyLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateCopyLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_COPY_LAMBDA_IR_FUNCTION_H
