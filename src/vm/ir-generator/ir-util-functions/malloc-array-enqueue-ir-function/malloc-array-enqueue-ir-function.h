//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_MALLOC_ARRAY_ENQUEUE_IR_FUNCTION_H
#define JETLANG_MALLOC_ARRAY_ENQUEUE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MallocArrayEnqueueIRFunction {
public:
    static std::string getMallocArrayEnqueueIRFunctionName();
    static void generateMallocArrayEnqueueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_MALLOC_ARRAY_ENQUEUE_IR_FUNCTION_H
