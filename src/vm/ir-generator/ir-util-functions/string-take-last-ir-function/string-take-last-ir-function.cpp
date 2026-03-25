//
// Created by Johny Georges on 2026-03-23.
//

#include "string-take-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringTakeLastIRFunction::getStringTakeLastIRFunctionName() {
    return "jet.string.take.last";
}

void StringTakeLastIRFunction::generateStringTakeLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(),
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
    auto numChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto takeNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsZeroIfBlock->getBlock());

    // isNumElementsZeroIfBlock
    auto isNumCharsOne = isNumElementsZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numChars,
            irGenerator->generateIntConstant(1)
    );
    isNumElementsZeroIfBlock->getBuilder()->get()->CreateCondBr(isNumCharsOne, isNumElementsZeroIfThenBlock->getBlock(), isTakeLastNumNegativeIfBlock->getBlock());

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
            { irGenerator->generateInt64Constant(1), sizeInBytes }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), emptyTakeStringMalloc, isNumElementsZeroIfThenBlock, charType);
    auto arrayPointerAllocationForEmptyTake = isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsZeroIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(1),
            depth,
            arrayPointerAllocationForEmptyTake,
            emptyTakeStringMalloc
    );
    auto loadedEmptyTake = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForEmptyTake, isNumElementsZeroIfThenBlock, arrayPointerType);
    isNumElementsZeroIfThenBlock->getBuilder()->get()->CreateRet(loadedEmptyTake);

    // isTakeNumGreaterThanNumElementsIfBlock
    auto isTakeNumGreaterThanNumElements = isTakeLastNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            takeNumElements,
            numChars
    );
    isTakeLastNumGreaterThanNumElementsIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumGreaterThanNumElements, isTakeLastNumGreaterThanNumElementsIfThenBlock->getBlock(), successorBlock->getBlock());

    // isTakeNumGreaterThanNumElementsIfThenBlock
    auto arrayPointerAllocationForFullCopy = isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(0) }
    );
    auto loadedFullTakeArray = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForFullCopy, isTakeLastNumGreaterThanNumElementsIfThenBlock, arrayPointerType);
    isTakeLastNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateRet(loadedFullTakeArray);

    auto totalTakeNumElements = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            takeNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto takeStringSize = successorBlock->getBuilder()->get()->CreateCall(
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
    auto arrayToTakeOffsetNumElements = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numChars, totalTakeNumElements);
    auto arrayToTakeOffsetInBytes = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                arrayToTakeOffsetNumElements,
                sizeInBytes
            }
    );
    auto pointerToStringWithOffset = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToString, { arrayToTakeOffsetInBytes });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { takeStringMalloc, pointerToStringWithOffset, takeStringSize }
    );
    auto arrayPointerAllocationForTakeLast = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            totalTakeNumElements,
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
    auto loadedTakeLastString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForTakeLastCopy, successorBlock, arrayPointerType);
    successorBlock->getBuilder()->get()->CreateRet(loadedTakeLastString);
}