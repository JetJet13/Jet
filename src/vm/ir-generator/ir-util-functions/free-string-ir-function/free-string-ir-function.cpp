//
// Created by Johny Georges on 2025-05-01.
//

#include "free-string-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string FreeStringIRFunction::getFreeStringIRFunctionName() {
    return "jet.free.string";
}

void FreeStringIRFunction::declareFreeStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStringIRFunction::getFreeStringIRFunctionName(), irModuleNode->getModule());
}

void FreeStringIRFunction::generateFreeStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto charType = new IRType(irGenerator->generateCharType());
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);

    auto function = irModuleNode->getFreeStringFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto sourceAllocationPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedSourceAllocation = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), sourceAllocationPointer);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { loadedSourceAllocation }
    );
    functionBlock->addVoidReturn();
}