//
// Created by Johny Georges on 2025-05-14.
//

#include "setup-sref-ir-function.h"

std::string SetupSrefIRFunction::getSetupSrefIRFunctionName() {
    return "jet.setup.sref";
}

void SetupSrefIRFunction::generateSetupSrefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupSrefIRFunction::getSetupSrefIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto refValueIndex = irGenerator->generateIntConstant(refType->getRefValueIndex());
    auto refCounterIndex = irGenerator->generateIntConstant(refType->getRefCounterIndex());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(1), { zeroIndex, refCounterIndex });
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(refType->getRefCounterIRType()->getType(), refCounterPointer, "currentRefCount");
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    functionBlock->getBuilder()->get()->CreateStore(newRefCount, refCounterPointer);

    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(1), { zeroIndex, refValueIndex });
    auto refValuePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefValuePointer);
    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refValueIndex });
    functionBlock->getBuilder()->get()->CreateStore(refValuePointer, pointerToNewRefValuePointer);

    auto pointerToNewRefCounterPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refCounterIndex });
    functionBlock->getBuilder()->get()->CreateStore(refCounterPointer, pointerToNewRefCounterPointer);

    functionBlock->addVoidReturn();
}