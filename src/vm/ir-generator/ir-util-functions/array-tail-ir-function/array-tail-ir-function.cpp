//
// Created by Johny Georges on 2025-06-05.
//

#include "array-tail-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayTailIRFunction::getArrayTailIRFunctionName() {
    return "jet.array.tail";
}

void ArrayTailIRFunction::generateArrayTailFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayTailIRFunction::getArrayTailIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsLessThanTwoIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNumElementsLessThanTwoIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getSizeInBytesIndex() }, "sizeInBytes");
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto numElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsLessThanTwoIfBlock->getBlock());

    // isNumElementsLessThanTwoIfBlock
    auto isNumElementsLessThanTwo = isNumElementsLessThanTwoIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            numElements,
            irGenerator->generateIntConstant(2)
    );
    isNumElementsLessThanTwoIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsLessThanTwo, isNumElementsLessThanTwoIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNumElementsLessThanTwoIfThenBlock
    auto emptyTailArrayMalloc = isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { irGenerator->generateIntConstant(0) }
    );
    auto arrayPointerAllocationForEmptyTail = isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsLessThanTwoIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(0),
            depth,
            arrayPointerAllocationForEmptyTail,
            emptyTailArrayMalloc
    );
    isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForEmptyTail);

    auto tailNumElements = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numElements, irGenerator->generateIntConstant(1));
    auto tailArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                tailNumElements,
                sizeInBytes
            }
    );
    auto tailArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { tailArraySize }
    );
    auto pointerToArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToArray);
    auto secondElementPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToArray, { sizeInBytes });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { tailArrayMalloc, secondElementPointer, tailArraySize }
    );
    auto arrayPointerAllocationForTail = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            tailNumElements,
            depth,
            arrayPointerAllocationForTail,
            tailArrayMalloc
    );
    auto arrayPointerAllocationForTailCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    successorBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getCopyArrayFunction()->getFunctionType(),
        irModuleNode->getCopyArrayFunction(),
        { arrayPointerAllocationForTailCopy, arrayPointerAllocationForTail, function->getArg(1) }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeArrayFunction()->getFunctionType(),
            irModuleNode->getFreeArrayFunction(),
            { arrayPointerAllocationForTail, function->getArg(1) }
    );
    successorBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForTailCopy);
}