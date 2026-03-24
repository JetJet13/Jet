//
// Created by Johny Georges on 2026-03-23.
//

#include "string-tail-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string StringTailIRFunction::getStringTailIRFunctionName() {
    return "jet.string.tail";
}

void StringTailIRFunction::generateStringTailFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringTailIRFunction::getStringTailIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsLessThanTwoIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsLessThanTwoIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
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
    auto emptyTailStringMalloc = isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(0), irGenerator->generateInt64Constant(1) }
    );
    auto arrayPointerAllocationForEmptyTail = isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsLessThanTwoIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(0),
            depth,
            arrayPointerAllocationForEmptyTail,
            emptyTailStringMalloc
    );
    isNumElementsLessThanTwoIfThenBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForEmptyTail);

    auto tailNumElements = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numElements, irGenerator->generateIntConstant(1));
    auto tailStringSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    tailNumElements,
                    sizeInBytes
            }
    );
    auto tailStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { tailNumElements, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    auto secondElementPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToString, { sizeInBytes });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { tailStringMalloc, secondElementPointer, tailStringSize }
    );
    auto arrayPointerAllocationForTail = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                    irGenerator->generateInt64Constant(1),
                    irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            tailNumElements,
            depth,
            arrayPointerAllocationForTail,
            tailStringMalloc
    );
    auto arrayPointerAllocationForTailCopy = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                    irGenerator->generateInt64Constant(1),
                    irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForTailCopy, arrayPointerAllocationForTail }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeStringFunction(),
            { arrayPointerAllocationForTail }
    );
    successorBlock->getBuilder()->get()->CreateRet(arrayPointerAllocationForTailCopy);
}