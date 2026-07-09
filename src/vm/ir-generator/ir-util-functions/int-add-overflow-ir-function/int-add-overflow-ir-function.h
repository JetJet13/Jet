//
// Created by Johny Georges on 2026-05-16.
//

#ifndef JETLANG_INT_ADD_OVERFLOW_IR_FUNCTION_H
#define JETLANG_INT_ADD_OVERFLOW_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class IntAddOverflowIRFunction {
public:
    static std::string getIntAddOverflowIRFunctionName();
    static void generateIntAddOverflowFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_INT_ADD_OVERFLOW_IR_FUNCTION_H
