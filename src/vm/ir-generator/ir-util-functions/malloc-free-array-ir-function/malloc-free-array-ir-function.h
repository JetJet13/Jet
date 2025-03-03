//
// Created by Johny Georges on 2025-03-03.
//

#ifndef JETLANG_MALLOC_FREE_ARRAY_IR_FUNCTION_H
#define JETLANG_MALLOC_FREE_ARRAY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MallocFreeArrayIRFunction {
public:
    static std::string getMallocFreeArrayIRFunctionName();
    static void generateMallocFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_MALLOC_FREE_ARRAY_IR_FUNCTION_H
