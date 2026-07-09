//
// Created by Johny Georges on 2025-12-30.
//

#ifndef JETLANG_INCREMENT_LAMBDA_REF_COUNT_IR_FUNCTION_H
#define JETLANG_INCREMENT_LAMBDA_REF_COUNT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class IncrementLambdaRefCountIRFunction {
public:
    static std::string getIncrementLambdaRefCountIRFunctionName();
    static void generateIncrementLambdaRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};


#endif //JETLANG_INCREMENT_LAMBDA_REF_COUNT_IR_FUNCTION_H
