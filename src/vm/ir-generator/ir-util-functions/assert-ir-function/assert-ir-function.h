//
// Created by Johny Georges on 2025-10-18.
//

#ifndef JETLANG_ASSERT_IR_FUNCTION_H
#define JETLANG_ASSERT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class AssertIRFunction {
public:
    static std::string getAssertIRFunctionName();
    static std::string getAssertWithMessageIRFunctionName();
    static std::string getAssertDebugRefCountIRFunctionName();
    static std::string getAssertDebugStructRefCountIRFunctionName();
    static std::string getAssertDebugLambdaRefCountIRFunctionName();
    static std::string getGlobalDefaultAssertMessageStringName();
    static std::string getGlobalAssertDebugRefCountMessageStringName();
    static std::string getGlobalAssertDebugStructRefCountMessageStringName();
    static std::string getGlobalAssertDebugLambdaRefCountMessageStringName();
    static void generateAssertGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertDebugGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertWithMessageFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertDebugRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertDebugStructRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generateAssertDebugLambdaRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_ASSERT_IR_FUNCTION_H
