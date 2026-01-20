//
// Created by Johny Georges on 2025-12-10.
//

#ifndef JETLANG_INCREMENT_REF_COUNT_IR_FUNCTION_H
#define JETLANG_INCREMENT_REF_COUNT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class IncrementRefCountIRFunction {
public:
    static std::string getIncrementRefCountIRFunctionName();
    static void generateIncrementRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_INCREMENT_REF_COUNT_IR_FUNCTION_H
