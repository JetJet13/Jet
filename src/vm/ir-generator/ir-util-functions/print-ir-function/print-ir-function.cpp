//
// Created by Johny Georges on 2024-10-12.
//

#include "print-ir-function.h"

std::string PrintIRFunction::getPrintIRFunctionName() {
    return "printf";
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(llvm::Type::getInt32Ty(**context), { llvm::Type::getInt8Ty(**context) }, true));
}