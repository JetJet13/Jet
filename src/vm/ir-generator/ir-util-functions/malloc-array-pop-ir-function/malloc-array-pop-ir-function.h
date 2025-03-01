//
// Created by Johny Georges on 2025-03-01.
//

#ifndef JETLANG_MALLOC_ARRAY_POP_IR_FUNCTION_H
#define JETLANG_MALLOC_ARRAY_POP_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MallocArrayPopIRFunction {
public:
    static std::string getMallocArrayPopIRFunctionName();
    static void generateMallocArrayPopFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_MALLOC_ARRAY_POP_IR_FUNCTION_H
