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
    auto isNumCharsOneIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumCharsOneIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumGreaterThanNumCharsIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeLastNumGreaterThanNumCharsIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto successorBlock = functionBlock->getLastChildOrSelf();
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getDepthIndex());
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto numChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numCharsPointer);
    auto takeNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumCharsOneIfBlock->getBlock());

    // isNumCharsZeroIfBlock
    auto isNumCharsOne = isNumCharsOneIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numChars,
            irGenerator->generateIntConstant(1)
    );
    isNumCharsOneIfBlock->getBuilder()->get()->CreateCondBr(isNumCharsOne, isNumCharsOneIfThenBlock->getBlock(), isTakeLastNumNegativeIfBlock->getBlock());

    // isTakeLastNumNegativeIfBlock
    auto isTakeLastNumNegative = isTakeLastNumNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            takeNumChars,
            irGenerator->generateIntConstant(0)
    );
    isTakeLastNumNegativeIfBlock->getBuilder()->get()->CreateCondBr(isTakeLastNumNegative, isNumCharsOneIfThenBlock->getBlock(), isTakeLastNumGreaterThanNumCharsIfBlock->getBlock());


    // isNumCharsOneIfThenBlock
    auto emptyTakeStringMalloc = isNumCharsOneIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(1), sizeInBytes }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), emptyTakeStringMalloc, isNumCharsOneIfThenBlock, charType);
    auto arrayPointerAllocationForEmptyTake = isNumCharsOneIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isNumCharsOneIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(1),
            depth,
            arrayPointerAllocationForEmptyTake,
            emptyTakeStringMalloc
    );
    auto loadedEmptyTake = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForEmptyTake, isNumCharsOneIfThenBlock, arrayPointerType);
    isNumCharsOneIfThenBlock->getBuilder()->get()->CreateRet(loadedEmptyTake);

    // isTakeNumGreaterThanNumCharsIfBlock
    auto isTakeNumGreaterThanNumChars = isTakeLastNumGreaterThanNumCharsIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            takeNumChars,
            numChars
    );
    isTakeLastNumGreaterThanNumCharsIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumGreaterThanNumChars, isTakeLastNumGreaterThanNumCharsIfThenBlock->getBlock(), successorBlock->getBlock());

    // isTakeLastNumGreaterThanNumCharsIfThenBlock
    auto arrayPointerAllocationForFullCopy = isTakeLastNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    isTakeLastNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(0) }
    );
    auto loadedFullTakeArray = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForFullCopy, isTakeLastNumGreaterThanNumCharsIfThenBlock, arrayPointerType);
    isTakeLastNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateRet(loadedFullTakeArray);

    auto totalTakeNumChars = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            takeNumChars,
            irGenerator->generateIntConstant(1)
    );
    auto takeStringSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                totalTakeNumChars,
                sizeInBytes
            }
    );
    auto takeStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { totalTakeNumChars, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    auto arrayToTakeOffsetNumChars = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numChars, totalTakeNumChars);
    auto arrayToTakeOffsetInBytes = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                arrayToTakeOffsetNumChars,
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
            totalTakeNumChars,
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
            irModuleNode->getFreeStringFunction(),
            { arrayPointerAllocationForTakeLast }
    );
    auto loadedTakeLastString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForTakeLastCopy, successorBlock, arrayPointerType);
    successorBlock->getBuilder()->get()->CreateRet(loadedTakeLastString);
}