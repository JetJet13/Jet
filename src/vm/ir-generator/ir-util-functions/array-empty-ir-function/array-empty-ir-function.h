//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_ARRAY_EMPTY_IR_FUNCTION_H
#define JETLANG_ARRAY_EMPTY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayEmptyIRFunction {
public:
    static std::string getArrayEmptyIRFunctionName();
    static void generateArrayEmptyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_ARRAY_EMPTY_IR_FUNCTION_H
