//
// Created by Johny Georges on 2026-03-27.
//

#ifndef JETLANG_STRING_APPEND_IR_FUNCTION_H
#define JETLANG_STRING_APPEND_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringAppendIRFunction {
public:
    static std::string getStringAppendIRFunctionName();
    static void generateStringAppendFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_APPEND_IR_FUNCTION_H
