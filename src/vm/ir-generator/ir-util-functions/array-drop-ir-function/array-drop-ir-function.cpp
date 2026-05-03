//
// Created by Johny Georges on 2025-06-02.
//

#include "array-drop-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string ArrayDropIRFunction::getArrayDropIRFunctionName() {
    return "jet.array.drop";
}

void ArrayDropIRFunction::generateArrayDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
        { pointerType->getType(), pointerType->getType(), typeValueType->getType() },
        false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayDropIRFunction::getArrayDropIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto successorBlock = functionBlock->getLastChildOrSelf();
    functionBlock->createChild();
    auto forLoopPrepBlock = functionBlock->getLastChildOrSelf();
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, functionBlock->getScope());
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, functionBlock->getScope());
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, functionBlock->getScope());

    auto numElementsIndex = arrayPointerType->getNumElementsIndex();
    auto allocIndex = arrayPointerType->getAllocIndex();
    auto depthIndex = arrayPointerType->getDepthIndex();
    auto sizeInBytesIndex = typeValueType->getSizeInBytesIndex();
    auto arrayElementTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValuePointer, sizeInBytesIndex);
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, arrayElementSizeInBytesPointer, "sizeInBytes");
    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), arrayElementTypeValuePointer);
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), depthIndex);
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), numElementsIndex);
    auto requestedNumElementsToDrop = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto numElementsToDropAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    functionBlock->getBuilder()->get()->CreateStore(requestedNumElementsToDrop, numElementsToDropAllocation);
    auto newNumElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumElements, requestedNumElementsToDrop);
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, newNumElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            newNumElements,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), newNumElementsAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(oldNumElements, numElementsToDropAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto pointerToOldArray = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), allocIndex);
    auto sourceArray = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToOldArray, successorBlock);
    auto numElementsToDrop = InstructionIRInjectorHelper::injectLoad(intType, numElementsToDropAllocation, successorBlock);
    auto loadedNewNumElements = InstructionIRInjectorHelper::injectLoad(intType, newNumElementsAllocation, successorBlock, {}, "newNumElements");
    auto newArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNewNumElements,
                sizeInBytes
            }
    );
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { loadedNewNumElements, sizeInBytes }
    );
    auto oldArrayOffset = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, sizeInBytes, numElementsToDrop);
    DebugIRInjectorHelper::injectLog(successorBlock, oldArrayOffset, irGenerator->getInjector(), irModuleNode);
    auto oldArrayOffsetPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, sourceArray, { oldArrayOffset });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, oldArrayOffsetPointer, newArraySize }
    );

    successorBlock->getBuilder()->get()->CreateStore(loadedNewNumElements, numElementsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToOldArray);
    successorBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

    // for loop prep block
    auto elementByteOffset = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, forLoopPrepBlock);
    auto forLoopIndex = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, forLoopPrepBlock);
    forLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto elementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, forLoopConditionBlock);
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
    auto forLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numElementsToDrop
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(forLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto pointerToElementAtIndex = forLoopBody->CreateInBoundsGEP(pointerIntType, sourceArray, { elementByteOffsetValue });
    forLoopBody->CreateCall(
            irContext->getIRModule()->getFreeValueFunction(),
            { pointerToElementAtIndex, elementTypeValue }
    );
    auto newElementByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, sizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, elementByteOffset, forLoopBodyBlock);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopBodyBlock);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    forLoopEndBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { sourceArray }
    );
    forLoopEndBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}