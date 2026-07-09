//
// Created by Johny Georges on 2025-10-13.
//

#ifndef JETLANG_EQUAL_STRUCT_IR_FUNCTION_H
#define JETLANG_EQUAL_STRUCT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualStructIRFunction {
public:
    static std::string getEqualStructIRFunctionName();
    static void declareEqualStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_STRUCT_IR_FUNCTION_H
