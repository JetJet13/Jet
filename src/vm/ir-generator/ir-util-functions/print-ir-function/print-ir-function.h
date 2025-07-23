//
// Created by Johny Georges on 2024-10-12.
//

#ifndef JETLANG_PRINT_IR_FUNCTION_H
#define JETLANG_PRINT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class PrintIRFunction {
private:
    static llvm::AllocaInst* generateStringAllocation(IRBlockNode* irBlock, std::vector<char> formatString, IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
public:
    static std::string getPrintIntIRFunctionName();
    static std::string getPrintFloatIRFunctionName();
    static std::string getPrintCharIRFunctionName();
    static std::string getPrintBoolIRFunctionName();
    static std::string getPrintStringIRFunctionName();
    static void generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintFloatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintCharFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintBoolFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_PRINT_IR_FUNCTION_H
