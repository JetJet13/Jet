//
// Created by Johny Georges on 2024-09-23.
//

#ifndef JETLANG_ARRAY_ACCESS_IR_FUNCTION_H
#define JETLANG_ARRAY_ACCESS_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayAccessIRFunction {
public:
    static std::string getArrayAccessIRFunctionName();
    static void generateArrayAccessFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_ACCESS_IR_FUNCTION_H
