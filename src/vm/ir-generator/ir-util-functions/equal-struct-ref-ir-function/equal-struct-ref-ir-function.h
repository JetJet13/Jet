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
    static void declareEqualStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateEqualStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_EQUAL_STRUCT_REF_IR_FUNCTION_H
