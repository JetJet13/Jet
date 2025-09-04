//
// Created by Johny Georges on 2025-02-22.
//

#include "malloc-size-ir-function.h"

std::string MallocSizeIRFunction::getMallocSizeIRFunctionName() {
    return "jet.malloc.size";
}

void MallocSizeIRFunction::generateMallocSizeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto functionType = llvm::FunctionType::get(irGenerator->generateIntType(), {irGenerator->generateIntType(), irGenerator->generateIntType() }, false);


    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocSizeIRFunction::getMallocSizeIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto numElements = function->getArg(0);
    auto elementSize = function->getArg(1);
    auto mallocSize = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, numElements, elementSize);

    functionBlock->getBuilder()->get()->CreateRet(mallocSize);
}