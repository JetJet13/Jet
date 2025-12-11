//
// Created by Johny Georges on 2025-12-05.
//

#ifndef JETLANG_FREE_CAPTURED_VARIABLE_IR_FUNCTION_H
#define JETLANG_FREE_CAPTURED_VARIABLE_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class FreeCapturedVariableIRFunction {
public:
    static std::string getFreeCapturedVariableIRFunctionName();
    static void declareFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};


#endif //JETLANG_FREE_CAPTURED_VARIABLE_IR_FUNCTION_H
