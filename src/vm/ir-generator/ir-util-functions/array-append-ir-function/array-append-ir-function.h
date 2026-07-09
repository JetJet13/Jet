//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_ARRAY_APPEND_IR_FUNCTION_H
#define JETLANG_ARRAY_APPEND_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayAppendIRFunction {
public:
    static std::string getArrayAppendIRFunctionName();
    static void generateArrayAppendFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_ARRAY_APPEND_IR_FUNCTION_H
