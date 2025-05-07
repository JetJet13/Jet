//
// Created by Johny Georges on 2025-05-01.
//

#ifndef JETLANG_FREE_STRING_IR_FUNCTION_H
#define JETLANG_FREE_STRING_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeStringIRFunction {
public:
    static std::string getFreeStringIRFunctionName();
    static void declareFreeStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_FREE_STRING_IR_FUNCTION_H
