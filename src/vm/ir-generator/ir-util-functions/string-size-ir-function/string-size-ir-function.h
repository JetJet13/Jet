//
// Created by Johny Georges on 2026-03-23.
//

#ifndef JETLANG_STRING_SIZE_IR_FUNCTION_H
#define JETLANG_STRING_SIZE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class StringSizeIRFunction {
public:
    static std::string getStringSizeIRFunctionName();
    static void generateStringSizeFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_STRING_SIZE_IR_FUNCTION_H
