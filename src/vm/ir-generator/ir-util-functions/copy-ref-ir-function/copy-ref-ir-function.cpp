//
// Created by Johny Georges on 2025-05-14.
//

#include "copy-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyRefIRFunction::getCopyRefIRFunctionName() {
    return "jet.copy.ref";
}

void CopyRefIRFunction::declareCopyRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyRefIRFunction::getCopyRefIRFunctionName(), irModuleNode->getModule()->get());
}

void CopyRefIRFunction::generateCopyRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);

    auto function = irModuleNode->getCopyRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValue = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1),  refType->getRefValueIndex());
    auto loadedPointerToRefValue = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefValuePointer);
    InstructionIRInjectorHelper::injectStore(loadedPointerToRefValue, pointerToNewRefValue, functionBlock);

    auto pointerToNewRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    auto pointerToRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1),  refType->getRefCounterIndex());
    auto loadedPointerToRefCounter = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounter);
    InstructionIRInjectorHelper::injectStore(loadedPointerToRefCounter, pointerToNewRefCounter, functionBlock);

    auto currentRefCount = InstructionIRInjectorHelper::injectLoad(refType->getRefCounterIRType()->getType(), loadedPointerToRefCounter, functionBlock);
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    InstructionIRInjectorHelper::injectStore(newRefCount, loadedPointerToRefCounter, functionBlock);

    functionBlock->addVoidReturn();
}