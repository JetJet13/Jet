//
// Created by Johny Georges on 2026-01-07.
//

#ifndef JETLANG_STRING_CONCAT_IR_FUNCTION_H
#define JETLANG_STRING_CONCAT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringConcatIRFunction {
public:
    static std::string getStringConcatIRFunctionName();
    static void generateStringConcatFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_CONCAT_IR_FUNCTION_H
