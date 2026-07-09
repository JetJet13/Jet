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
    static std::string getGlobalLambdaStartFormatStringName();
    static std::string getGlobalLambdaPointerFormatStringName();
    static std::string getGlobalLambdaEndFormatStringName();
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
    static std::string getPrintLambdaIRFunctionName();
    static std::string getPrintWhitespaceIRFunctionName();
    static std::string getPrintCommaIRFunctionName();
    static std::string getPrintNewLineIRFunctionName();
    static std::string getPrintDebugMarkerIRFunctionName();
    static std::string getPrintDebugPointerIRFunctionName();
    static std::string getPrintDebugStringIRFunctionName();
    static std::string getPrintDebugRefCountIRFunctionName();
    static void declarePrintDebugMarkerFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintDebugPointerFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintDebugStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintDebugRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintWhitespaceFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintCommaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintNewLineFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintArrayFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void declarePrintStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintDebugGlobals(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintGlobals(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintIntFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintFloatFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintCharFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintBoolFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintArrayFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintWhitespaceFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintCommaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintNewLineFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintDebugMarkerFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintDebugPointerFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintDebugStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
    static void generatePrintDebugRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode);
};

#endif //JETLANG_PRINT_IR_FUNCTION_H
