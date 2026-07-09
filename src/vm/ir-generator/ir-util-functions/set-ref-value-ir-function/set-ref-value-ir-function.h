//
// Created by Johny Georges on 2026-02-16.
//

#ifndef JETLANG_SET_REF_VALUE_IR_FUNCTION_H
#define JETLANG_SET_REF_VALUE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SetRefValueIRFunction {
public:
    static std::string getSetRefValueIRFunctionName();
    static void generateSetRefValueFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SET_REF_VALUE_IR_FUNCTION_H
