//
// Created by Johny Georges on 2025-05-14.
//

#ifndef JETLANG_SETUP_SREF_IR_FUNCTION_H
#define JETLANG_SETUP_SREF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SetupSrefIRFunction {
public:
    static std::string getSetupSrefIRFunctionName();
    static void generateSetupSrefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_SETUP_SREF_IR_FUNCTION_H
