//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_ARRAY_SIZE_IR_FUNCTION_H
#define JETLANG_ARRAY_SIZE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArraySizeIRFunction {
public:
    static std::string getArraySizeIRFunctionName();
    static void generateArraySizeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_SIZE_IR_FUNCTION_H
