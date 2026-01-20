//
// Created by Johny Georges on 2025-10-13.
//

#ifndef JETLANG_EQUAL_ARRAY_IR_FUNCTION_H
#define JETLANG_EQUAL_ARRAY_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualArrayIRFunction {
public:
    static std::string getEqualArrayIRFunctionName();
    static void declareEqualArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_ARRAY_IR_FUNCTION_H
