//
// Created by Johny Georges on 2025-03-01.
//

#include "array-prepend-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string ArrayPrependIRFunction::getArrayPrependIRFunctionName() {
    return "jet.array.prepend";
}

void ArrayPrependIRFunction::generateArrayPrependFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(),
                                                {
                                                    pointerType->getType(),
                                                    pointerType->getType(),
                                                    typeValueType->getType()
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayPrependIRFunction::getArrayPrependIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto arrayElementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValue, typeValueType->getSizeInBytesIndex());
    auto sizeInBytes = InstructionIRInjectorHelper::injectLoad(intType, arrayElementSizeInBytesPointer, functionBlock);
    //    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, arrayElementSizeInBytesPointer, "sizeInBytes");
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto oldNumElements = InstructionIRInjectorHelper::injectLoad(intType, numElementsPointer, functionBlock);
//    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
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
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, function->getArg(1), sizeInBytes }
    );
    auto newArraySecondElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, {sizeInBytes });
    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToOldArray = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToOldArray, functionBlock);
//    auto loadedPointerToOldArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArraySecondElementPointer, loadedPointerToOldArray, oldArraySize }
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
