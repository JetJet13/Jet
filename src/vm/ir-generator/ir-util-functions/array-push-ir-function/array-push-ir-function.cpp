//
// Created by Johny Georges on 2025-03-01.
//

#include "array-push-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayPushIRFunction::getArrayPushIRFunctionName() {
    return "jet.array.push";
}

void ArrayPushIRFunction::generateArrayPushFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(),
                                                {
                                                    pointerType->getType(),
                                                    pointerType->getType(),
                                                    typeValueType->getType()
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayPushIRFunction::getArrayPushIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto sizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(2), { zeroIndex, sizeInBytesIndex });
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, sizeInBytesPointer);
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, oldNumElements, irGenerator->generateIntConstant(1));
    auto oldArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    oldNumElements,
                    sizeInBytes
            }
    );
    auto newArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    newNumElements,
                    sizeInBytes
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { newArraySize }
    );

    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToOldArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, loadedPointerToOldArray, oldArraySize }
    );
    auto newElementByteOffsetIndex = oldArraySize;
    auto newElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { newElementByteOffsetIndex });
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newElementPointer, function->getArg(1), sizeInBytes }
    );
    auto arrayPointerAllocationForOldArray = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            functionBlock,
            arrayPointerType,
            oldNumElements,
            depth,
            arrayPointerAllocationForOldArray,
            loadedPointerToOldArray
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeArrayFunction()->getFunctionType(),
            irModuleNode->getFreeArrayFunction(),
            { arrayPointerAllocationForOldArray, function->getArg(2) }
    );
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, numElementsPointer);
    functionBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToOldArray);
    functionBlock->addVoidReturn();
}