//
// Created by Johny Georges on 2025-02-22.
//

#ifndef JETLANG_MALLOC_IR_FUNCTION_H
#define JETLANG_MALLOC_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MallocIRFunction {
public:
    static std::string getMallocIRFunctionName();
    static void generateMallocFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_MALLOC_IR_FUNCTION_H
