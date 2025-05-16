//
// Created by Johny Georges on 2025-05-16.
//

#ifndef JETLANG_SETUP_REF_IR_FUNCTION_H
#define JETLANG_SETUP_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SetupRefIRFunction {
public:
    static std::string getSetupRefIRFunctionName();
    static void generateSetupRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_SETUP_REF_IR_FUNCTION_H
