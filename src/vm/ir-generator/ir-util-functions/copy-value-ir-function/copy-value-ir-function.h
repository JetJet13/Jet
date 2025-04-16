//
// Created by Johny Georges on 2025-04-16.
//

#ifndef JETLANG_COPY_VALUE_IR_FUNCTION_H
#define JETLANG_COPY_VALUE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class CopyValueIRFunction {
public:
    static std::string getCopyValueIRFunctionName();
    static void generateCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};


#endif //JETLANG_COPY_VALUE_IR_FUNCTION_H
