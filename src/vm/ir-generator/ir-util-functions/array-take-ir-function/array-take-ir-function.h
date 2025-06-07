//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_ARRAY_TAKE_IR_FUNCTION_H
#define JETLANG_ARRAY_TAKE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayTakeIRFunction {
public:
    static std::string getArrayTakeIRFunctionName();
    static void generateArrayTakeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_TAKE_IR_FUNCTION_H
