//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_ARRAY_PUSH_IR_FUNCTION_H
#define JETLANG_ARRAY_PUSH_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayPushIRFunction {
public:
    static std::string getArrayPushIRFunctionName();
    static void generateArrayPushFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_PUSH_IR_FUNCTION_H
