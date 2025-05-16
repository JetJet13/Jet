//
// Created by Johny Georges on 2025-05-16.
//

#include "setup-ref-ir-function.h"

std::string SetupRefIRFunction::getSetupRefIRFunctionName() {
    return "jet.setup.ref";
}

void SetupRefIRFunction::generateSetupRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupRefIRFunction::getSetupRefIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto refValueIndex = irGenerator->generateIntConstant(refType->getRefValueIndex());
    auto refCounterIndex = irGenerator->generateIntConstant(refType->getRefCounterIndex());


    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refValueIndex });
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), pointerToNewRefValuePointer);

    auto intType = IRType(irGenerator->generateIntType());
    auto refCounterMalloc = functionBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMallocFunction()->getFunctionType(),
        irModuleNode->getMallocFunction(),
        { irGenerator->generateIntConstant(intType.getSizeInBytes()) }
    );
    auto refCounter = functionBlock->getBuilder()->get()->CreateBitCast(refCounterMalloc, intType.getType()->getPointerTo());
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), refCounter);
    auto pointerToNewRefCounterPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refCounterIndex });
    functionBlock->getBuilder()->get()->CreateStore(refCounterMalloc, pointerToNewRefCounterPointer);

    functionBlock->addVoidReturn();
}