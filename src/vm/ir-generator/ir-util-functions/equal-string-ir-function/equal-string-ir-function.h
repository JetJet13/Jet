//
// Created by Johny Georges on 2025-10-13.
//

#ifndef JETLANG_EQUAL_STRING_IR_FUNCTION_H
#define JETLANG_EQUAL_STRING_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualStringIRFunction {
public:
    static std::string getEqualStringIRFunctionName();
    static void declareEqualStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_STRING_IR_FUNCTION_H
