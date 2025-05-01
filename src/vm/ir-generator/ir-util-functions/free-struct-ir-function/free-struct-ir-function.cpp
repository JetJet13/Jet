//
// Created by Johny Georges on 2025-04-30.
//

#include "free-struct-ir-function.h"

std::string FreeStructIRFunction::getFreeStructIRFunctionName() {
    return "jet.free.struct";
}

void FreeStructIRFunction::declareFreeStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStructIRFunction::getFreeStructIRFunctionName(), irModuleNode->getModule());
}

void FreeStructIRFunction::generateFreeStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto numTypesIndex = irGenerator->generateIntConstant(typeValueType->getNumTypesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());

    auto numTypesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { zeroIndex, numTypesIndex });
    auto loadedNumTypes = functionBlock->getBuilder()->get()->CreateLoad(intType, numTypesPointer);

    auto elementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            loadedNumTypes
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto pointerToTypeValueAllocAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { zeroIndex, allocIndex });
    auto loadedTypeValueAllocAtIndex = forLoopBody->CreateLoad(pointerType->getType(), pointerToTypeValueAllocAtIndex);
    auto pointerToTypeValueAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), loadedTypeValueAllocAtIndex, { forLoopIndexValue });
    auto typeValueAtIndex = forLoopBody->CreateLoad(typeValueType->getType(), pointerToTypeValueAtIndex);
    auto structByteOffsetValue = forLoopBody->CreateLoad(intType, elementByteOffset);

    auto pointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), {structByteOffsetValue });
    forLoopBody->CreateCall(
            irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeValueFunction(),
            { pointerAtIndex, typeValueAtIndex }
    );

    auto sizeInBytesAtIndexPointer = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), typeValueAtIndex, { zeroIndex, sizeInBytesIndex });
    auto loadedSizeInBytesAtIndex = forLoopBody->CreateLoad(intType, sizeInBytesAtIndexPointer);
    auto newStructByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, loadedSizeInBytesAtIndex);
    forLoopBody->CreateStore(elementByteOffset, newStructByteOffsetValue);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(forLoopIndex, newForLoopIndexValue);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());

    functionEndBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFreeFunction(),
            { function->getArg(0) }
    );
    functionEndBlock->addVoidReturn();
}