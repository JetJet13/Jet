//
// Created by Johny Georges on 2025-03-01.
//

#include "array-push-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string ArrayPushIRFunction::getArrayPushIRFunctionName() {
    return "jet.array.push";
}

void ArrayPushIRFunction::generateArrayPushFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(),
                                                {
                                                    irGenerator->generatePointerType(arrayPointerType->getType()),
                                                    irGenerator->generatePointerType(arrayPointerType->getType())
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayPushIRFunction::getArrayPushIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, loadedNumElements, irGenerator->generateIntConstant(1));
    auto newElement = functionBlock->getBuilder()->get()->CreateAlloca(pointerType->getType());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), newElement);
    auto oldArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    loadedNumElements,
                    irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
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
    auto newArrayMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(newArrayMalloc, arrayPointerType->getType());
    auto loadedNewElement = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), newElement);
    auto newElementIndex = functionBlock->getBuilder()->get()->getInt32(0);
    auto newElementPointer = functionBlock->getBuilder()->get()->CreateGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, newElementIndex });
    functionBlock->getBuilder()->get()->CreateStore(loadedNewElement, newElementPointer);
    auto newArrayMallocWithFirstElementOffset = functionBlock->getBuilder()->get()->CreateInBoundsGEP(newArrayMallocBitCast->getType(), newArrayMallocBitCast, { zeroIndex, irGenerator->generateIntConstant(1) });
    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateMemCpy(
            newArrayMallocWithFirstElementOffset,
            DataAlignmentGenerator::generate(arrayPointerType),
            pointerToOldArray,
            DataAlignmentGenerator::generate(arrayPointerType),
            oldArraySize
    );
    auto stackNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, stackNumElementsPointer);
    auto stackNumLevelsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(arrayPointerType->getDepth()), stackNumLevelsPointer);
    auto stackAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(newArrayMallocBitCast, stackAllocPointer);
    functionBlock->addVoidReturn();
}