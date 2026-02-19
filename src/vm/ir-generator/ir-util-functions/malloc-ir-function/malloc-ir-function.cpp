//
// Created by Johny Georges on 2025-02-22.
//

#include "malloc-ir-function.h"

std::string MallocIRFunction::getMallocIRFunctionName() {
    return "jet.malloc";
}

void MallocIRFunction::generateMallocFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { intType, intType }, false);
    auto calloc = irModuleNode->getModule()->get()->getOrInsertFunction("calloc", functionType);
    auto raise = irModuleNode->getModule()->get()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocIRFunction::getMallocIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto allocatedPointer = functionBlock->getBuilder()->get()->CreateCall(calloc, { function->getArg(0), function->getArg(1) });
    auto isAllocatedPointerNull = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            allocatedPointer,
            llvm::ConstantPointerNull::get(pointerType->getType())
    );
    auto successBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    successBlock->getBuilder()->get()->CreateRet(allocatedPointer);

    auto errorBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto segFaultCode = irGenerator->generateIntConstant(11);
    errorBlock->getBuilder()->get()->CreateCall(raise, { segFaultCode });
    errorBlock->addVoidReturn();
    functionBlock->getBuilder()->get()->CreateCondBr(isAllocatedPointerNull, successBlock->getBlock(), errorBlock->getBlock());
}