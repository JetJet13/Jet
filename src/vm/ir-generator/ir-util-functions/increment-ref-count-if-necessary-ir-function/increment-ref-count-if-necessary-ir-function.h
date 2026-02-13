//
// Created by Johny Georges on 2026-02-12.
//

#ifndef JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H
#define JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

// We shouldn't need this function since calling CopyValue should take care of incrementing
// the ref count. That being said, I will leave this in just in case I discover an edge case
// where its needed.
class IncrementRefCountIfNecessaryIRFunction {
public:
    static std::string getIncrementRefCountIfNecessaryIRFunctionName();
    static void generateIncrementRefCountIfNecessaryFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_INCREMENT_REF_COUNT_IF_NECESSARY_IR_FUNCTION_H
