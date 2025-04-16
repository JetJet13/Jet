//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-struct-ir-function.h"

std::string CopyStructIRFunction::getCopyStructIRFunctionName() {
    return "jet.copy.struct";
}

void CopyStructIRFunction::generateCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(**context), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStructIRFunction::getCopyStructIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    functionBlock->addVoidReturn();
}