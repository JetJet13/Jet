//
// Created by Johny Georges on 2025-05-16.
//

#ifndef JETLANG_SETUP_SHARED_PTR_IR_FUNCTION_H
#define JETLANG_SETUP_SHARED_PTR_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class SetupSharedPtrIRFunction {
public:
    static std::string getSetupSharedPtrIRFunctionName();
    static void generateSetupSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_SETUP_SHARED_PTR_IR_FUNCTION_H
