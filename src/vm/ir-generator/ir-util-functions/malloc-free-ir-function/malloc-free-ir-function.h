//
// Created by Johny Georges on 2025-02-22.
//

#ifndef JETLANG_MALLOC_FREE_IR_FUNCTION_H
#define JETLANG_MALLOC_FREE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MallocFreeIRFunction {
public:
    static std::string getMallocFreeIRFunctionName();
    static void generateMallocFreeFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_MALLOC_FREE_IR_FUNCTION_H
