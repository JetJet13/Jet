//
// Created by Johny Georges on 2025-04-15.
//

#ifndef JETLANG_MEMCPY_IR_FUNCTION_H
#define JETLANG_MEMCPY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class MemcpyIRFunction {
public:
    static std::string getMemcpyIRFunctionName();
    static void generateMemcpyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};


#endif //JETLANG_MEMCPY_IR_FUNCTION_H
