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
    static std::string getGlobalDefaultAssertMessageStringName();
    static std::string getGlobalAssertWithMessageStringName();
    static void generateAssertGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateAssertFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generateAssertWithMessageFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_ASSERT_IR_FUNCTION_H
