//
// Created by Johny Georges on 2026-03-23.
//

#include "string-take-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string StringTakeLastIRFunction::getStringTakeLastIRFunctionName() {
    return "jet.string.take.last";
}

void StringTakeLastIRFunction::generateStringTakeLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringTakeLastIRFunction::getStringTakeLastIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsZeroIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumGreaterThanNumElementsIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumGreaterThanNumElementsIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getDepthIndex());
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto numElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto takeNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsZeroIfBlock->getBlock());

    // isNumElementsZeroIfBlock
    auto isNumElementsNegative = isNumElementsZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numElements,
            irGenerator->generateIntConstant(0)
    );
    isNumElementsZeroIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsNegative, isNumElementsZeroIfThenBlock->getBlock(), isTakeLastNumNegativeIfBlock->getBlock());

    // isTakeNumNegativeIfBlock
    auto isTakeNumNegative = isTakeLastNumNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            takeNumElements,
            irGenerator->generateIntConstant(0)
    );
    isTakeLastNumNegativeIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumNegative, isNumElementsZeroIfThenBlock->getBlock(), isTakeLastNumGreaterThanNumElementsIfBlock->getBlock());


    // isNumElementsZeroIfThenBlock
    auto emptyTakeStringMalloc = isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(0), irGenerator->generateInt64Constant(1) }
    );
    auto arrayPointerAllocationForEmptyTake = isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsZeroIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(0),
            depth,
            arrayPointerAllocationForEmptyTake,
            emptyTakeStringMalloc
    );
    isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForEmptyTake);

    // isTakeNumGreaterThanNumElementsIfBlock
    auto isTakeNumGreaterThanNumElements = isTakeLastNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            takeNumElements,
            numElements
    );
    isTakeLastNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumGreaterThanNumElements, isTakeLastNumGreaterThanNumElementsIfThenBlock->getBlock(), successorBlock->getBlock());

    // isTakeNumGreaterThanNumElementsIfThenBlock
    auto arrayPointerAllocationForFullCopy = isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(0) }
    );
    isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForFullCopy);


    auto totalTakeNumElements = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            takeNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto takeStringSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    totalTakeNumElements,
                    sizeInBytes
            }
    );
    auto takeStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { totalTakeNumElements, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    auto arrayToTakeOffsetNumElements = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numElements, takeNumElements);
    auto arrayToTakeOffsetInBytes = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                arrayToTakeOffsetNumElements,
                sizeInBytes
            }
    );
    auto pointerToStringWithOffset = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToString, { arrayToTakeOffsetInBytes });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { takeStringMalloc, pointerToStringWithOffset, takeStringSize }
    );
    auto arrayPointerAllocationForTakeLast = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            takeNumElements,
            depth,
            arrayPointerAllocationForTakeLast,
            takeStringMalloc
    );
    auto arrayPointerAllocationForTakeLastCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForTakeLastCopy, arrayPointerAllocationForTakeLast }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { takeStringMalloc }
    );
    successorBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForTakeLastCopy);
}