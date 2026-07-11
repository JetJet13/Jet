//
// Created by Johny Georges on 2026-03-27.
//

#include "string-prepend-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringPrependIRFunction::getStringPrependIRFunctionName() {
    return "jet.string.prepend";
}

void StringPrependIRFunction::generateStringPrependFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(),
                                                {
                                                    pointerType->getType(),
                                                    pointerType->getType(),
                                                },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringPrependIRFunction::getStringPrependIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto oldNumChars = InstructionIRInjectorHelper::injectLoad(intType, numElementsPointer, functionBlock);
    auto newNumChars = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, oldNumChars, irGenerator->generateIntConstant(1));
    auto oldArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    oldNumChars,
                    sizeInBytes
            }
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { newNumChars, sizeInBytes }
    );

    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, function->getArg(1), sizeInBytes }
    );
    auto newArraySecondElementPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { sizeInBytes });
    auto pointerToOldArray = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToOldArray = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToOldArray, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArraySecondElementPointer, loadedPointerToOldArray, oldArraySize }
    );

    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { loadedPointerToOldArray }
    );
    InstructionIRInjectorHelper::injectStore(newNumChars, numElementsPointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(newArrayMalloc, pointerToOldArray, functionBlock);
    functionBlock->addVoidReturn();
}