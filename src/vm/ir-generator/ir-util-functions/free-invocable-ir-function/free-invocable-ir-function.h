//
// Created by Johny Georges on 2026-01-01.
//

#ifndef JETLANG_FREE_INVOCABLE_IR_FUNCTION_H
#define JETLANG_FREE_INVOCABLE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeInvocableIRFunction {
public:
    static std::string getFreeInvocableIRFunctionName();
    static void declareFreeInvocableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeInvocableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_FREE_INVOCABLE_IR_FUNCTION_H
