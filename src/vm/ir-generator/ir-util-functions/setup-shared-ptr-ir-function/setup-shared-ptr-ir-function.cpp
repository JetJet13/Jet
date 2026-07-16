//
// Created by Johny Georges on 2025-05-16.
//

#include "setup-shared-ptr-ir-function.h"

std::string SetupSharedPtrIRFunction::getSetupSharedPtrIRFunctionName() {
    return "jet.setup.shared.ptr";
}

void SetupSharedPtrIRFunction::generateSetupSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           SetupSharedPtrIRFunction::getSetupSharedPtrIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getSharedValueIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), pointerToNewRefValuePointer);

    auto intType = IRType(irGenerator->generateIntType());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0),
                                                                                          sharedPtrType->getRefCounterIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(2), pointerToRefCounterPointer);
    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getIncrementRefCountFunction(), { function->getArg(0) });
    functionBlock->addVoidReturn();
}