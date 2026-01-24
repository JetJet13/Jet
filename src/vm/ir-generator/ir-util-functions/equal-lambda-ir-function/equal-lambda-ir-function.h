//
// Created by Johny Georges on 2026-01-21.
//

#ifndef JETLANG_EQUAL_LAMBDA_IR_FUNCTION_H
#define JETLANG_EQUAL_LAMBDA_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualLambdaIRFunction {
public:
    static std::string getEqualLambdaIRFunctionName();
    static void declareEqualLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_LAMBDA_IR_FUNCTION_H
