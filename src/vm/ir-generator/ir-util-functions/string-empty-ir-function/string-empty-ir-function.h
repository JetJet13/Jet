//
// Created by Johny Georges on 2026-03-23.
//

#ifndef JETLANG_STRING_EMPTY_IR_FUNCTION_H
#define JETLANG_STRING_EMPTY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringEmptyIRFunction {
public:
    static std::string getStringEmptyIRFunctionName();
    static void generateStringEmptyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_EMPTY_IR_FUNCTION_H
