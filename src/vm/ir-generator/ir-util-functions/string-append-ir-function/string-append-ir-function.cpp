//
// Created by Johny Georges on 2026-03-27.
//

#include "string-append-ir-function.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringAppendIRFunction::getStringAppendIRFunctionName() {
    return "jet.string.append";
}

void StringAppendIRFunction::generateStringAppendFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(
            irGenerator->getVoidType(),
            {
                pointerType->getType(),
                pointerType->getType(),
            },
            false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringAppendIRFunction::getStringAppendIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
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
    auto newElementByteOffsetIndex = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldArraySize, sizeInBytes);
    auto newCharPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, {newElementByteOffsetIndex });
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newCharPointer, function->getArg(1), sizeInBytes }
    );

    auto terminatorCharPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { oldArraySize });
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), terminatorCharPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { loadedPointerToOldArray }
    );
    InstructionIRInjectorHelper::injectStore(newNumElements, numElementsPointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(newArrayMalloc, pointerToOldArray, functionBlock);
    functionBlock->addVoidReturn();
}