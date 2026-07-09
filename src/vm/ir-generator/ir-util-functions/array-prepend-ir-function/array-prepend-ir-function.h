//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_ARRAY_PREPEND_IR_FUNCTION_H
#define JETLANG_ARRAY_PREPEND_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayPrependIRFunction {
public:
    static std::string getArrayPrependIRFunctionName();
    static void generateArrayPrependFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_ARRAY_PREPEND_IR_FUNCTION_H
