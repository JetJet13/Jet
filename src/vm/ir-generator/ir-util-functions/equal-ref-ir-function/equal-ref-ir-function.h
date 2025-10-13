//
// Created by Johny Georges on 2025-10-13.
//

#ifndef JETLANG_EQUAL_REF_IR_FUNCTION_H
#define JETLANG_EQUAL_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualRefIRFunction {
public:
    static std::string getEqualRefIRFunctionName();
    static void declareEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_EQUAL_REF_IR_FUNCTION_H
