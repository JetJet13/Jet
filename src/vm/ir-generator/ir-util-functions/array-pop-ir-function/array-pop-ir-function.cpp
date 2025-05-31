//
// Created by Johny Georges on 2025-03-01.
//

#include "array-pop-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string ArrayPopIRFunction::getArrayPopIRFunctionName() {
    return "jet.array.pop";
}

void ArrayPopIRFunction::generateArrayPopFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType,
                                                { pointerType, intType },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayPopIRFunction::getArrayPopIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto lastElementIndex = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            loadedNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto lastElement = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getArrayAccessFunction()->getFunctionType(),
            irModuleNode->getArrayAccessFunction(),
            { function->getArg(0), lastElementIndex, function->getArg(1) }
    );
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
    // todo: complete this. Remember to create a new array with 1 less element
    //    functionBlock->getBuilder()->get()->CreateRet(loadedLastElement);
}