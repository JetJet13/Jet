//
// Created by Johny Georges on 2025-03-01.
//

#include "malloc-array-enqueue-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string MallocArrayEnqueueIRFunction::getMallocArrayEnqueueIRFunctionName() {
    return "jet.malloc.array.enqueue";
}

void MallocArrayEnqueueIRFunction::generateMallocArrayEnqueueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto mallocArrayType = irGenerator->generateIrMallocArrayType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(mallocArrayType);
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(),
                                                { irGenerator->generatePointerType(arrayPointerType->getType()),
                                                  irGenerator->generatePointerType(mallocArrayType->getType())
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocArrayEnqueueIRFunction::getMallocArrayEnqueueIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto firstElementPointerIndex = irGenerator->generateIntConstant(arrayPointerType->getPointerIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, zeroIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, loadedNumElements, irGenerator->generateIntConstant(1));
    auto newElement = functionBlock->getBuilder()->get()->CreateAlloca(pointerType->getType());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), newElement);
    auto oldArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNumElements,
                irGenerator->generateIntConstant(mallocArrayType->getSizeInBytes())
            }
    );
    auto newArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    newNumElements,
                    irGenerator->generateIntConstant(mallocArrayType->getSizeInBytes())
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { newArraySize }
    );
    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateMemCpy(
            newArrayMalloc,
            DataAlignmentGenerator::generate(mallocArrayType),
            pointerToOldArray,
            DataAlignmentGenerator::generate(mallocArrayType),
            oldArraySize
    );
    auto newArrayMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(newArrayMalloc, mallocArrayType->getType());
    auto loadedNewElement = functionBlock->getBuilder()->get()->CreateLoad(mallocArrayType->getType(), newElement);
    auto newElementIndex = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, newNumElements, irGenerator->generateIntConstant(1));
    auto newElementPointer = functionBlock->getBuilder()->get()->CreateGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, newElementIndex });
    functionBlock->getBuilder()->get()->CreateStore(loadedNewElement, newElementPointer);
    auto queueNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, queueNumElementsPointer);
    auto queueFirstElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, firstElementPointerIndex });
    auto queueFirstElement = functionBlock->getBuilder()->get()->CreateInBoundsGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(queueFirstElement, queueFirstElementPointer);
    auto queueAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(newArrayMallocBitCast, queueAllocPointer);
    functionBlock->addVoidReturn();
}

/*
 * { i32, ptr, ptr } @jet.malloc.array.enqueue(ptr %0, ptr %1):
 * entry:
 *      %numElements = load i32 (gep {i32, ptr, ptr} %0 { 0, 0 })
 *      %newNumElements = add i32 %numElements, i32 1
 *      %newElement = load { i32, { i32, ptr, ptr } } %1
 *      %newArray = alloca { i32, { i32, ptr, ptr } }, i32 %newNumElements;
 *      %pointerToOldArray = gep { i32, ptr, ptr } %0 { 0, 2 }
 *      %oldArraySize = call @jet.malloc.size(%numElements, i32 10);
 *      call void @llvm.memcpy.p0.p0.i64(ptr %newArray, ptr %pointerToOldArray, i64 %oldArraySize, i1 false)
 *      %newElementIndex = sub i32 %newNumElements, i32 1
 *      %newElementPointer = gep ptr %newArray { 0, %newElementIndex }
 *      store %newElement, %newElementPointer
 *      %newArraySize = call @jet.malloc.size(%newNumElements, i32 10);
 *      %malloc = call ptr @jet.malloc(%newArraySize)
 *      call void @llvm.memcpy.p0.p0.i64(ptr %malloc, ptr %newArray, i64 %newArraySize, i1 false)
 *      %newQueue = alloca { i32, ptr, ptr }
 *      store i32 %newNumElements, gep { i32, ptr, ptr } %newQueue { 0, 0 }
 *      %malloc_array = bitcast i8* %malloc to { i32, { i32, ptr, ptr } }*
 *      store ptr gep %malloc_array { 0, 0 }, gep { i32, ptr, ptr } %newQueue { 0, 1 }
 *      store ptr %malloc_array, gep { i32, ptr, ptr } %newQueue { 0, 2 }
 *      return %newQueue
 * */