//
// Created by Johny Georges on 2025-03-01.
//

#include "malloc-array-push-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string MallocArrayPushIRFunction::getMallocArrayPushIRFunctionName() {
    return "jet.malloc.array.push";
}

void MallocArrayPushIRFunction::generateMallocArrayPushFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto mallocArrayType = irGenerator->generateIrMallocArrayType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(mallocArrayType);
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(),
                                                { irGenerator->generatePointerType(arrayPointerType->getType()),
                                                  irGenerator->generatePointerType(mallocArrayType->getType())
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocArrayPushIRFunction::getMallocArrayPushIRFunctionName(), irModuleNode->getModule());
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
    auto newArrayMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(newArrayMalloc, mallocArrayType->getType());
    auto loadedNewElement = functionBlock->getBuilder()->get()->CreateLoad(mallocArrayType->getType(), newElement);
    auto newElementIndex = functionBlock->getBuilder()->get()->getInt32(0);
    auto newElementPointer = functionBlock->getBuilder()->get()->CreateGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, newElementIndex });
    functionBlock->getBuilder()->get()->CreateStore(loadedNewElement, newElementPointer);
    auto newArrayMallocWithFirstElementOffset = functionBlock->getBuilder()->get()->CreateInBoundsGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, irGenerator->generateIntConstant(1) });
    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateMemCpy(
            newArrayMallocWithFirstElementOffset,
            DataAlignmentGenerator::generate(mallocArrayType),
            pointerToOldArray,
            DataAlignmentGenerator::generate(mallocArrayType),
            oldArraySize
    );
    auto stackNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, stackNumElementsPointer);
    auto stackFirstElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, firstElementPointerIndex });
    auto stackFirstElement = functionBlock->getBuilder()->get()->CreateInBoundsGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(stackFirstElement, stackFirstElementPointer);
    auto stackAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(newArrayMallocBitCast, stackAllocPointer);
    functionBlock->addVoidReturn();
}