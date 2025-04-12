//
// Created by Johny Georges on 2025-03-01.
//

#include "malloc-array-pop-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string MallocArrayPopIRFunction::getMallocArrayPopIRFunctionName() {
    return "jet.malloc.array.dequeue";
}

void MallocArrayPopIRFunction::generateMallocArrayPopFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(),
                                                { irGenerator->generatePointerType(arrayPointerType->getType()) },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           MallocArrayPopIRFunction::getMallocArrayPopIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, loadedNumElements, irGenerator->generateIntConstant(1));
    auto newArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                newNumElements,
                irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { newArraySize }
    );
    auto pointerToSecondElementInOldArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex, irGenerator->generateIntConstant(1) });
    functionBlock->getBuilder()->get()->CreateMemCpy(
            newArrayMalloc,
            DataAlignmentGenerator::generate(arrayPointerType),
            pointerToSecondElementInOldArray,
            DataAlignmentGenerator::generate(arrayPointerType),
            newArraySize
    );
    auto newArrayMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(newArrayMalloc, arrayPointerType->getType());

    auto queueNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, queueNumElementsPointer);
    auto queueNumLevelsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(arrayPointerType->getDepth()), queueNumLevelsPointer);
    auto queueAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(newArrayMallocBitCast, queueAllocPointer);
    functionBlock->addVoidReturn();
}

/*
 * void @jet.malloc.array.dequeue(ptr %0):
 * entry:
 *      %numElements = load i32 (gep {i32, ptr, ptr} %0 { 0, 0 })
 *      %newNumElements = sub i32 %numElements, i32 1
 *      // update the alloc value to a new smaller malloc
 *      %newMallocSize = call @jet.malloc.size(%newNumElements, i32 10)
 *      %newMalloc = call @jet.malloc(%newMallocSize)
 *      %oldMallocWithOffsetFirstElement = gep {i32, ptr, ptr} %0 { 0, 2, 1 }
 *      call void @llvm.memcpy.p0.p0.i64(ptr %newMalloc, ptr %oldMallocWithOffsetFirstElement, i64 %newMallocSize, i1 false)
 *      %newMallocBitCast = bitcast i8* %newMalloc to { i32, { i32, ptr, ptr } }*
 *      store %newMallocBitCast, gep { i32, ptr, ptr } %0 { 0, 2 }
 *
 *      // update the pointer value to the next element in the array
 *      %newFirstElement = ptr gep { i32, { i32, ptr, ptr } } %newMallocBitCase { 0, 0 }
 *      store %newFirstElement, gep { i32, ptr, ptr } %0 { 0, 1 }
 *
 *      // update the num elements value to %newNumElements
 *      store %newNumElements, gep { i32, ptr, ptr } %0 { 0, 0 }
 *      ret 0
 * */