//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_ARRAY_TAKE_LAST_IR_FUNCTION_H
#define JETLANG_ARRAY_TAKE_LAST_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class ArrayTakeLastIRFunction {
public:
    static std::string getArrayTakeLastIRFunctionName();
    static void generateArrayTakeLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_ARRAY_TAKE_LAST_IR_FUNCTION_H
