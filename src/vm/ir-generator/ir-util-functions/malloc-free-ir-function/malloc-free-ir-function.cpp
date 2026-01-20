//
// Created by Johny Georges on 2025-02-22.
//

#include "malloc-free-ir-function.h"

std::string MallocFreeIRFunction::getMallocFreeIRFunctionName() {
    return "jet.malloc.free";
}

void MallocFreeIRFunction::generateMallocFreeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { irGenerator->generatePointerType() }, false);
    auto free = irModuleNode->getModule()->get()->getOrInsertFunction("free", functionType);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocFreeIRFunction::getMallocFreeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    functionBlock->getBuilder()->get()->CreateCall(free, { function->getArg(0) });
    functionBlock->addVoidReturn();
}