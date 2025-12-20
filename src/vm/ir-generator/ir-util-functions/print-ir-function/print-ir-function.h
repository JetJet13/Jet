//
// Created by Johny Georges on 2024-10-12.
//

#ifndef JETLANG_PRINT_IR_FUNCTION_H
#define JETLANG_PRINT_IR_FUNCTION_H

#include <utility>
#include "llvm/IR/IRBuilder.h"
#include "../../ir-generator.h"

class PrintIRFunction {
public:
    static std::string getGlobalIntFormatStringName();
    static std::string getGlobalFloatFormatStringName();
    static std::string getGlobalCharFormatStringName();
    static std::string getGlobalCharPrettyFormatStringName();
    static std::string getGlobalTrueFormatStringName();
    static std::string getGlobalFalseFormatStringName();
    static std::string getGlobalStringFormatStringName();
    static std::string getGlobalPointerFormatStringName();
    static std::string getGlobalCommaFormatStringName();
    static std::string getGlobalColonFormatStringName();
    static std::string getGlobalRefStartFormatStringName();
    static std::string getGlobalRefEndFormatStringName();
    static std::string getGlobalArrayStartFormatStringName();
    static std::string getGlobalArrayEndFormatStringName();
    static std::string getGlobalStructStartFormatStringName();
    static std::string getGlobalStructEndFormatStringName();
    static std::string getGlobalRefCountFormatStringName();
    static std::string getPrintIRFunctionName();
    static std::string getPrintIntIRFunctionName();
    static std::string getPrintFloatIRFunctionName();
    static std::string getPrintCharIRFunctionName();
    static std::string getPrintBoolIRFunctionName();
    static std::string getPrintStringIRFunctionName();
    static std::string getPrintRefIRFunctionName();
    static std::string getPrintArrayIRFunctionName();
    static std::string getPrintStructIRFunctionName();
    static std::string getPrintStructRefIRFunctionName();
    static std::string getPrintWhitespaceIRFunctionName();
    static std::string getPrintCommaIRFunctionName();
    static std::string getPrintNewLineIRFunctionName();
    static std::string getPrintDebugMarkerIRFunctionName();
    static std::string getPrintDebugPointerIRFunctionName();
    static std::string getPrintDebugStringIRFunctionName();
    static std::string getPrintDebugRefCountIRFunctionName();
    static void declarePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintDebugRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintCommaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void declarePrintStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintFloatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintCharFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintBoolFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintCommaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
    static void generatePrintDebugRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode);
};

#endif //JETLANG_PRINT_IR_FUNCTION_H
