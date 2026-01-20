//
// Created by Johny Georges on 2025-12-19.
//

#ifndef JETLANG_SETUP_REF_FOR_STRUCT_IR_FUNCTION_H
#define JETLANG_SETUP_REF_FOR_STRUCT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SetupRefForStructIRFunction {
public:
    static std::string getSetupRefForStructIRFunctionName();
    static void generateSetupRefForStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SETUP_REF_FOR_STRUCT_IR_FUNCTION_H
