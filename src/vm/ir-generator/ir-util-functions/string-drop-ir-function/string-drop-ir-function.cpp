//
// Created by Johny Georges on 2026-03-21.
//

#include "string-drop-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string StringDropIRFunction::getStringDropIRFunctionName() {
    return "jet.string.drop";
}

void StringDropIRFunction::generateStringDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringDropIRFunction::getStringDropIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto numElementsIndex = arrayPointerType->getNumElementsIndex();
    auto allocIndex = arrayPointerType->getAllocIndex();
    auto depthIndex = arrayPointerType->getDepthIndex();
    auto sizeInBytes = functionBlock->getBuilder()->get()->getInt64(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), depthIndex);
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), numElementsIndex);
    auto numElementsToDrop = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumElements, numElementsToDrop);
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, newNumElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            newNumElements,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), newNumElementsAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto loadedNewNumElements = successorBlock->getBuilder()->get()->CreateLoad(intType, newNumElementsAllocation, "newNumElements");
    auto newStringSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                    loadedNewNumElements,
                    sizeInBytes
            }
    );
    auto newStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { loadedNewNumElements, sizeInBytes }
    );
    auto oldStringOffset = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, sizeInBytes, numElementsToDrop);
    auto pointerToOldString = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), allocIndex);
    auto loadedPointerToOldString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldString);
    auto oldStringOffsetPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToOldString, { oldStringOffset });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newStringMalloc, oldStringOffsetPointer, newStringSize }
    );

    auto arrayPointerAllocationForOldString = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            oldNumElements,
            depth,
            arrayPointerAllocationForOldString,
            loadedPointerToOldString
    );
    successorBlock->getBuilder()->get()->CreateStore(loadedNewNumElements, numElementsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newStringMalloc, pointerToOldString);
//    successorBlock->getBuilder()->get()->CreateCall(
//        irModuleNode->getFreeStringFunction(),
//        { arrayPointerAllocationForOldString, function->getArg(2) }
//    );
    successorBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}