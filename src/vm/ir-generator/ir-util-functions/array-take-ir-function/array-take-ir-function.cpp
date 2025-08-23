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
                                                { pointerType->getType(), pointerType->getType(), typeValueType->getType() },
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
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto arrayElementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), arrayElementTypeValue, { zeroIndex, sizeInBytesIndex });
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, arrayElementSizeInBytesPointer, "sizeInBytes");
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto numElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto takeNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsZeroIfBlock->getBlock());

    // isNumElementsZeroIfBlock
    auto isNumElementsZero = isNumElementsZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numElements,
            irGenerator->generateIntConstant(0)
    );
    isNumElementsZeroIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsZero, isNumElementsZeroIfThenBlock->getBlock(), isTakeNumNegativeIfBlock->getBlock());

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
            { irGenerator->generateInt64Constant(0) }
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
            { arrayPointerAllocationForFullCopy, function->getArg(0), function->getArg(2) }
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
    auto pointerToArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
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
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintDebugMarkerFunction(),
            { sizeInBytes }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintWhitespaceFunction(),
            {}
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintDebugMarkerFunction(),
            { takeNumElements }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintWhitespaceFunction(),
            {}
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintDebugMarkerFunction(),
            { takeArraySize }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getPrintNewLineFunction(),
            { }
    );
    auto arrayPointerAllocationForTakeCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
//    successorBlock->getBuilder()->get()->CreateCall(
//            irModuleNode->getCopyArrayFunction()->getFunctionType(),
//            irModuleNode->getCopyArrayFunction(),
//            { arrayPointerAllocationForTakeCopy, arrayPointerAllocationForTake, function->getArg(2) }
//    );
//    successorBlock->getBuilder()->get()->CreateCall(
//            irModuleNode->getMallocFreeFunction()->getFunctionType(),
//            irModuleNode->getMallocFreeFunction(),
//            { takeArrayMalloc, takeNumElements }
//    );
    successorBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForTakeCopy);
}