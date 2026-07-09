//
// Created by Johny Georges on 2026-04-23.
//

#ifndef JETLANG_FREE_CLASS_PROPERTY_IR_FUNCTION_H
#define JETLANG_FREE_CLASS_PROPERTY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeClassPropertyIRFunction {
public:
    static std::string getFreeClassPropertyIRFunctionName();
    static void generateFreeClassPropertyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_FREE_CLASS_PROPERTY_IR_FUNCTION_H
