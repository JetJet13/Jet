//
// Created by Johny Georges on 2025-12-10.
//

#ifndef JETLANG_FREE_LAMBDA_IR_FUNCTION_H
#define JETLANG_FREE_LAMBDA_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeLambdaIRFunction {
public:
    static std::string getFreeLambdaIRFunctionName();
    static void declareFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_FREE_LAMBDA_IR_FUNCTION_H
