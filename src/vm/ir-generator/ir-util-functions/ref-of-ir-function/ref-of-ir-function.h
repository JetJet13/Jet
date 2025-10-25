//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_REF_OF_IR_FUNCTION_H
#define JETLANG_REF_OF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class RefOfIRFunction {
public:
    static std::string getRefOfIRFunctionName();
    static void generateRefOfFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_REF_OF_IR_FUNCTION_H
