//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-struct-ir-function.h"

std::string CopyStructIRFunction::getCopyStructIRFunctionName() {
    return "jet.copy.struct";
}

void CopyStructIRFunction::generateCopyStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(**context), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStructIRFunction::getCopyStructIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto numTypesIndex = irGenerator->generateIntConstant(typeValueType->getNumTypesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());

    auto numTypesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(2), { zeroIndex, numTypesIndex });
    auto loadedNumTypes = functionBlock->getBuilder()->get()->CreateLoad(intType, numTypesPointer);

    auto structByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "structByteOffset");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), structByteOffset);

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
    auto pointerToTypeValueAllocAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), function->getArg(2), { zeroIndex, allocIndex });
    auto loadedTypeValueAllocAtIndex = forLoopBody->CreateLoad(pointerType->getType(), pointerToTypeValueAllocAtIndex);
    auto pointerToTypeValueAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), loadedTypeValueAllocAtIndex, { forLoopIndexValue });
    auto typeValueAtIndex = forLoopBody->CreateLoad(typeValueType->getType(), pointerToTypeValueAtIndex);
    auto structByteOffsetValue = forLoopBody->CreateLoad(intType, structByteOffset);

    auto destinationPointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), { structByteOffsetValue });
    auto sourcePointerAtIndex = forLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(1), { structByteOffsetValue });
    forLoopBody->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationPointerAtIndex, sourcePointerAtIndex, typeValueAtIndex }
    );

    auto sizeInBytesAtIndexPointer = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), typeValueAtIndex, { zeroIndex, sizeInBytesIndex });
    auto loadedSizeInBytesAtIndex = forLoopBody->CreateLoad(intType, sizeInBytesAtIndexPointer);
    auto newStructByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, structByteOffsetValue, loadedSizeInBytesAtIndex);
    forLoopBody->CreateStore(structByteOffset, newStructByteOffsetValue);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(forLoopIndex, newForLoopIndexValue);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto functionEndBlock = irGenerator->generateBasicBlock("", irContext);
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionEndBlock->getBlock());

    functionEndBlock->addVoidReturn();
}