//
// Created by Johny Georges on 2025-05-16.
//

#include "setup-ref-ir-function.h"

std::string SetupRefIRFunction::getSetupRefIRFunctionName() {
    return "jet.setup.ref";
}

void SetupRefIRFunction::generateSetupRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupRefIRFunction::getSetupRefIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), pointerToNewRefValuePointer);

    auto intType = IRType(irGenerator->generateIntType());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(2), pointerToRefCounterPointer);
    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getIncrementRefCountFunction(), { function->getArg(0) });
    functionBlock->addVoidReturn();
}