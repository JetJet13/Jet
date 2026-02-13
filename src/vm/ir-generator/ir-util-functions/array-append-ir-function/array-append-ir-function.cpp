//
// Created by Johny Georges on 2025-03-01.
//

#include "array-append-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string ArrayAppendIRFunction::getArrayAppendIRFunctionName() {
    return "jet.array.append";
}

void ArrayAppendIRFunction::generateArrayAppendFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(
        irGenerator->getVoidType(),
        {
            pointerType->getType(),
            pointerType->getType(),
            typeValueType->getType()
        },
        false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayAppendIRFunction::getArrayAppendIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto arrayElementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValue, typeValueType->getSizeInBytesIndex());
    auto sizeInBytes = InstructionIRInjectorHelper::injectLoad(intType, arrayElementSizeInBytesPointer, functionBlock);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto oldNumElements = InstructionIRInjectorHelper::injectLoad(intType, numElementsPointer, functionBlock);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, oldNumElements, irGenerator->generateIntConstant(1));
    auto oldArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                oldNumElements,
                sizeInBytes
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { newNumElements, sizeInBytes }
    );

    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToOldArray = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToOldArray, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, loadedPointerToOldArray, oldArraySize }
    );
    auto newElementByteOffsetIndex = oldArraySize;
    auto newElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { newElementByteOffsetIndex });
    auto loadedArrayElementTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), arrayElementTypeValue, functionBlock, typeValueType);

    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyValueFunction(),
            { newElementPointer, function->getArg(1), loadedArrayElementTypeValue }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { loadedPointerToOldArray }
    );
    InstructionIRInjectorHelper::injectStore(newNumElements, numElementsPointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(newArrayMalloc, pointerToOldArray, functionBlock);
    functionBlock->addVoidReturn();
}