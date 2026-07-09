//
// Created by Johny Georges on 2025-12-22.
//

#ifndef JETLANG_EQUAL_STRUCT_REF_IR_FUNCTION_H
#define JETLANG_EQUAL_STRUCT_REF_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualStructRefIRFunction {
public:
    static std::string getEqualStructRefIRFunctionName();
    static void declareEqualStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_STRUCT_REF_IR_FUNCTION_H
