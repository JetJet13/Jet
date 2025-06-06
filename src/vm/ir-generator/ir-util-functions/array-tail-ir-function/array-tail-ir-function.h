//
// Created by Johny Georges on 2025-06-05.
//

#ifndef JETLANG_ARRAY_TAIL_IR_FUNCTION_H
#define JETLANG_ARRAY_TAIL_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayTailIRFunction {
public:
    static std::string getArrayTailIRFunctionName();
    static void generateArrayTailFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_TAIL_IR_FUNCTION_H
