//
// Created by Johny Georges on 2024-10-12.
//

#ifndef JETLANG_PRINT_IR_FUNCTION_H
#define JETLANG_PRINT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class PrintIRFunction {
public:
    static std::string getPrintIRFunctionName();
    static void generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_PRINT_IR_FUNCTION_H
