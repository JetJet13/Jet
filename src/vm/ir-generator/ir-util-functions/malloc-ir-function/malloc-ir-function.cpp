//
// Created by Johny Georges on 2025-02-22.
//

#include "malloc-ir-function.h"

std::string MallocIRFunction::getMallocIRFunctionName() {
    return "jet.malloc";
}

void MallocIRFunction::generateMallocFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto mallocSizeType = irGenerator->generateInt64Type();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { mallocSizeType }, false);
    auto malloc = irModuleNode->getModule()->getOrInsertFunction("malloc", functionType);
    auto raise = irModuleNode->getModule()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocIRFunction::getMallocIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto allocatedPointer = functionBlock->getBuilder()->get()->CreateCall(malloc, { function->getArg(0) });
    auto isAllocatedPointerNull = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            allocatedPointer,
            llvm::ConstantPointerNull::get(pointerType->getType())
    );
    auto successBlock = irGenerator->generateIfThenBlock(irContext);
    successBlock->getBuilder()->get()->CreateRet(allocatedPointer);

    auto errorBlock = irGenerator->generateIfElseBlock(irContext);
    auto segFaultCode = irGenerator->generateIntConstant(11);
    errorBlock->getBuilder()->get()->CreateCall(raise, { segFaultCode });
    errorBlock->addVoidReturn();
    functionBlock->getBuilder()->get()->CreateCondBr(isAllocatedPointerNull, successBlock->getBlock(), errorBlock->getBlock());
}