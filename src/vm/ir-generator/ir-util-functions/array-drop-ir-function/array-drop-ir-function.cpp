//
// Created by Johny Georges on 2025-06-02.
//

#include "array-drop-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayDropIRFunction::getArrayDropIRFunctionName() {
    return "jet.array.drop";
}

void ArrayDropIRFunction::generateArrayDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
        { pointerType->getType(), intType, typeValueType->getType() },
        false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayDropIRFunction::getArrayDropIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto sizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(2), { zeroIndex, sizeInBytesIndex });
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, sizeInBytesPointer, "sizeInBytes");
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumElements, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, newNumElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            newNumElements,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), newNumElementsAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto loadedNewNumElements = successorBlock->getBuilder()->get()->CreateLoad(intType, newNumElementsAllocation, "newNumElements");
    auto newArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    loadedNewNumElements,
                    sizeInBytes
            }
    );
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            {newArraySize }
    );
    auto oldArrayOffset = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, sizeInBytes, function->getArg(1));
    auto pointerToOldArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToOldArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    auto oldArrayOffsetPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToOldArray, { oldArrayOffset });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            {newArrayMalloc, oldArrayOffsetPointer, newArraySize }
    );

    auto arrayPointerAllocationForOldArray = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            functionBlock,
            arrayPointerType,
            oldNumElements,
            depth,
            arrayPointerAllocationForOldArray,
            loadedPointerToOldArray
    );
    successorBlock->getBuilder()->get()->CreateStore(loadedNewNumElements, numElementsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToOldArray);
    successorBlock->addVoidReturn();
}