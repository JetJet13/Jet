//
// Created by Johny Georges on 2025-05-31.
//

#ifndef JETLANG_ARRAY_CONCAT_IR_FUNCTION_H
#define JETLANG_ARRAY_CONCAT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayConcatIRFunction {
public:
    static std::string getArrayConcatIRFunctionName();
    static void generateArrayConcatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_CONCAT_IR_FUNCTION_H
