//
// Created by Johny Georges on 2025-10-13.
//

#ifndef JETLANG_EQUAL_SHARED_PTR_IR_FUNCTION_H
#define JETLANG_EQUAL_SHARED_PTR_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class EqualSharedPtrIRFunction {
public:
    static std::string getEqualSharedPtrIRFunctionName();
    static std::string getEqualSharedPtrLeftOnlyIRFunctionName();
    static std::string getEqualSharedPtrRightOnlyIRFunctionName();
    static void declareEqualSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declareEqualSharedPtrLeftOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declareEqualSharedPtrRightOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualSharedPtrLeftOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateEqualSharedPtrRightOnlyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_EQUAL_SHARED_PTR_IR_FUNCTION_H
