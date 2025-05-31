//
// Created by Johny Georges on 2025-05-31.
//

#ifndef JETLANG_ARRAY_HEAD_IR_FUNCTION_H
#define JETLANG_ARRAY_HEAD_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayHeadIRFunction {
public:
    static std::string getArrayHeadIRFunctionName();
    static void generateArrayHeadFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_HEAD_IR_FUNCTION_H
