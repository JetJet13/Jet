//
// Created by Johny Georges on 2025-05-27.
//

#ifndef JETLANG_RANGE_IR_FUNCTION_H
#define JETLANG_RANGE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class RangeIRFunction {
public:
    static std::string getRangeIRFunctionName();
    static void generateRangeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_RANGE_IR_FUNCTION_H
