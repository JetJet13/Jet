//
// Created by Johny Georges on 2025-06-02.
//

#ifndef JETLANG_ARRAY_DROP_IR_FUNCTION_H
#define JETLANG_ARRAY_DROP_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayDropIRFunction {
public:
    static std::string getArrayDropIRFunctionName();
    static void generateArrayDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ARRAY_DROP_IR_FUNCTION_H
