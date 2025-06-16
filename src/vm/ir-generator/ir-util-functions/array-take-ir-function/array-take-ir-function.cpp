//
// Created by Johny Georges on 2025-06-07.
//

#include "array-take-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayTakeIRFunction::getArrayTakeIRFunctionName() {
    return "jet.array.take";
}

void ArrayTakeIRFunction::generateArrayTakeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { intType, pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayTakeIRFunction::getArrayTakeIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsZeroIfBlock = irGenerator->generateIfBlock(irContext);
    auto isTakeNumNegativeIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNumElementsZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isTakeNumGreaterThanNumElementsIfBlock = irGenerator->generateIfBlock(irContext);
    auto isTakeNumGreaterThanNumElementsIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getSizeInBytesIndex() }, "sizeInBytes");
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, numElementsIndex });
    auto numElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto takeNumElements = function->getArg(0);
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsZeroIfBlock->getBlock());

    // isNumElementsZeroIfBlock
    auto isNumElementsNegative = isNumElementsZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numElements,
            irGenerator->generateIntConstant(0)
    );
    isNumElementsZeroIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsNegative, isNumElementsZeroIfThenBlock->getBlock(), isTakeNumNegativeIfBlock->getBlock());

    // isTakeNumNegativeIfBlock
    auto isTakeNumNegative = isTakeNumNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            takeNumElements,
            irGenerator->generateIntConstant(0)
    );
    isTakeNumNegativeIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumNegative, isNumElementsZeroIfThenBlock->getBlock(), isTakeNumGreaterThanNumElementsIfBlock->getBlock());


    // isNumElementsZeroIfThenBlock
    auto emptyTakeArrayMalloc = isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { irGenerator->generateIntConstant(0) }
    );
    auto arrayPointerAllocationForEmptyTake = isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsZeroIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(0),
            depth,
            arrayPointerAllocationForEmptyTake,
            emptyTakeArrayMalloc
    );
    isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForEmptyTake);

    // isTakeNumGreaterThanNumElementsIfBlock
    auto isTakeNumGreaterThanNumElements = isTakeNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            takeNumElements,
            numElements
    );
    isTakeNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumGreaterThanNumElements, isTakeNumGreaterThanNumElementsIfThenBlock->getBlock(), successorBlock->getBlock());

    // isTakeNumGreaterThanNumElementsIfThenBlock
    auto arrayPointerAllocationForFullCopy = isTakeNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    isTakeNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyArrayFunction()->getFunctionType(),
            irModuleNode->getCopyArrayFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(1), function->getArg(2) }
    );
    isTakeNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForFullCopy);


    auto takeArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    takeNumElements,
                    sizeInBytes
            }
    );
    auto takeArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { takeArraySize }
    );
    auto pointerToArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, allocIndex });
    auto loadedPointerToArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToArray);
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { takeArrayMalloc, loadedPointerToArray, takeArraySize }
    );
    auto arrayPointerAllocationForTake = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            takeNumElements,
            depth,
            arrayPointerAllocationForTake,
            takeArrayMalloc
    );
    auto arrayPointerAllocationForTakeCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyArrayFunction()->getFunctionType(),
            irModuleNode->getCopyArrayFunction(),
            { arrayPointerAllocationForTakeCopy, arrayPointerAllocationForTake, function->getArg(2) }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { takeArrayMalloc, function->getArg(0) }
    );
    successorBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForTakeCopy);
}