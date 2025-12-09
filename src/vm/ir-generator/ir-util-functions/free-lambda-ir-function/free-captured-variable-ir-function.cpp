//
// Created by Johny Georges on 2025-12-05.
//

#include "free-captured-variable-ir-function.h"

std::string FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName() {
    return "jet.free.captured.variable";
}

void FreeCapturedVariableIRFunction::declareFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                           FreeCapturedVariableIRFunction::getFreeCapturedVariableIRFunctionName(), irModuleNode->getModule());
}

void FreeCapturedVariableIRFunction::generateFreeCapturedVariableFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeCapturedVariableFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    functionBlock->addVoidReturn();
}