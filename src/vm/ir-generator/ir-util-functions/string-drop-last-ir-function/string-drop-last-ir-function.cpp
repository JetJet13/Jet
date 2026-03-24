//
// Created by Johny Georges on 2026-03-21.
//

#include "string-drop-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string StringDropLastIRFunction::getStringDropLastIRFunctionName() {
    return "jet.string.drop.last";
}

void StringDropLastIRFunction::generateStringDropLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringDropLastIRFunction::getStringDropLastIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytes = functionBlock->getBuilder()->get()->getInt64(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numCharsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), {zeroIndex, numElementsIndex });
    auto numCharsToDrop = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    auto oldNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numCharsPointer);
    DebugIRInjectorHelper::injectLog(functionBlock, oldNumChars, irGenerator->getInjector(), irModuleNode);
    auto numCharsToKeepAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto numCharsToKeep = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumChars, numCharsToDrop);
    functionBlock->getBuilder()->get()->CreateStore(numCharsToKeep, numCharsToKeepAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            numCharsToKeep,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), numCharsToKeepAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto loadedNumCharsToKeep = successorBlock->getBuilder()->get()->CreateLoad(intType, numCharsToKeepAllocation, "numCharsToKeep");
    DebugIRInjectorHelper::injectLog(successorBlock, loadedNumCharsToKeep, irGenerator->getInjector(), irModuleNode);
    auto newArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNumCharsToKeep,
                sizeInBytes
            }
    );
    DebugIRInjectorHelper::injectLog(successorBlock, newArraySize, irGenerator->getInjector(), irModuleNode);
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { loadedNumCharsToKeep, sizeInBytes }
    );
    auto pointerToOldArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToOldArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    auto sizeToCopy = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, newArraySize, sizeInBytes);
    successorBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMemcpyFunction(),
        { newArrayMalloc, loadedPointerToOldArray, sizeToCopy }
    );
    DebugIRInjectorHelper::injectLog(successorBlock, sizeToCopy, irGenerator->getInjector(), irModuleNode);
    auto pointerToTerminatorPosition = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType->getType(), newArrayMalloc, { sizeToCopy });
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), pointerToTerminatorPosition, successorBlock, charType);

    auto arrayPointerAllocationForOldArray = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            oldNumChars,
            depth,
            arrayPointerAllocationForOldArray,
            loadedPointerToOldArray
    );
    successorBlock->getBuilder()->get()->CreateStore(loadedNumCharsToKeep, numCharsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToOldArray);
    successorBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getFreeStringFunction(),
        { arrayPointerAllocationForOldArray }
    );
    successorBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}