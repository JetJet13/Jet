//
// Created by Johny Georges on 2026-03-23.
//

#include "string-take-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringTakeIRFunction::getStringTakeIRFunctionName() {
    return "jet.string.take";
}

void StringTakeIRFunction::generateStringTakeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringTakeIRFunction::getStringTakeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumElementsOneIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeNumNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumElementsOneIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isTakeNumGreaterThanNumElementsIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeNumGreaterThanNumElementsIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
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
    auto takeNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumElementsOneIfBlock->getBlock());

    // isNumElementsOneIfBlock
    auto isNumElementsOne = isNumElementsOneIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numElements,
            irGenerator->generateIntConstant(1)
    );
    isNumElementsOneIfBlock->getBuilder()->get()->CreateCondBr(isNumElementsOne, isNumElementsOneIfThenBlock->getBlock(), isTakeNumNegativeIfBlock->getBlock());

    // isTakeNumNegativeIfBlock
    auto isTakeNumNegative = isTakeNumNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            takeNumElements,
            irGenerator->generateIntConstant(0)
    );
    isTakeNumNegativeIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumNegative, isNumElementsOneIfThenBlock->getBlock(), isTakeNumGreaterThanNumElementsIfBlock->getBlock());


    // isNumElementsOneIfThenBlock
    auto emptyTakeStringMalloc = isNumElementsOneIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(1), sizeInBytes }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), emptyTakeStringMalloc, isNumElementsOneIfThenBlock, charType);
    auto arrayPointerAllocationForEmptyTake = isNumElementsOneIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumElementsOneIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(1),
            depth,
            arrayPointerAllocationForEmptyTake,
            emptyTakeStringMalloc
    );
    auto loadedEmptyTake = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForEmptyTake, isNumElementsOneIfThenBlock, arrayPointerType);
    isNumElementsOneIfThenBlock->getBuilder()->get()->CreateRet(loadedEmptyTake);

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
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(0) }
    );
    auto loadedFullTakeString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForFullCopy, isTakeNumGreaterThanNumElementsIfThenBlock, arrayPointerType);
    isTakeNumGreaterThanNumElementsIfThenBlock->getBuilder()->get()->CreateRet(loadedFullTakeString);


    auto takeSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                takeNumElements,
                sizeInBytes
            }
    );
    auto totalTakeNumElements = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            takeNumElements,
            irGenerator->generateIntConstant(1)
    );
    auto takeStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { totalTakeNumElements, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { takeStringMalloc, loadedPointerToString, takeSize }
    );

    // append terminator char
    auto pointerToTerminatorPosition = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType->getType(), takeStringMalloc, { takeSize });
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), pointerToTerminatorPosition, successorBlock, charType);

    auto arrayPointerAllocationForTake = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            totalTakeNumElements,
            depth,
            arrayPointerAllocationForTake,
            takeStringMalloc
    );
    auto arrayPointerAllocationForTakeCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForTakeCopy, arrayPointerAllocationForTake }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { takeStringMalloc }
    );
    auto loadedTake = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForTakeCopy, successorBlock, arrayPointerType);
    successorBlock->getBuilder()->get()->CreateRet(loadedTake);
}