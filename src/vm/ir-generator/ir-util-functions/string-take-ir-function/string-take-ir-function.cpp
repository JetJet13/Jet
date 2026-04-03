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
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringTakeIRFunction::getStringTakeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumCharsOneIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeNumNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumCharsOneIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isTakeNumGreaterThanNumCharsIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isTakeNumGreaterThanNumCharsIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numCharsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numCharsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numCharsIndex });
    auto numChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numCharsPointer);
    auto takeNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    functionBlock->getBuilder()->get()->CreateBr(isNumCharsOneIfBlock->getBlock());

    // isNumCharsOneIfBlock
    auto isNumCharsOne = isNumCharsOneIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numChars,
            irGenerator->generateIntConstant(1)
    );
    isNumCharsOneIfBlock->getBuilder()->get()->CreateCondBr(isNumCharsOne, isNumCharsOneIfThenBlock->getBlock(), isTakeNumNegativeIfBlock->getBlock());

    // isTakeNumNegativeIfBlock
    auto isTakeNumNegative = isTakeNumNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            takeNumChars,
            irGenerator->generateIntConstant(0)
    );
    isTakeNumNegativeIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumNegative, isNumCharsOneIfThenBlock->getBlock(), isTakeNumGreaterThanNumCharsIfBlock->getBlock());


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
    auto isTakeNumGreaterThanNumChars = isTakeNumGreaterThanNumCharsIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            takeNumChars,
            numChars
    );
    isTakeNumGreaterThanNumCharsIfBlock->getBuilder()->get()->CreateCondBr(isTakeNumGreaterThanNumChars, isTakeNumGreaterThanNumCharsIfThenBlock->getBlock(), successorBlock->getBlock());

    // isTakeNumGreaterThanNumCharsIfThenBlock
    auto arrayPointerAllocationForFullCopy = isTakeNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    isTakeNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForFullCopy, function->getArg(0) }
    );
    auto loadedFullTakeString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForFullCopy, isTakeNumGreaterThanNumCharsIfThenBlock, arrayPointerType);
    isTakeNumGreaterThanNumCharsIfThenBlock->getBuilder()->get()->CreateRet(loadedFullTakeString);


    auto takeSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                takeNumChars,
                sizeInBytes
            }
    );
    auto totalTakeNumChars = successorBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            takeNumChars,
            irGenerator->generateIntConstant(1)
    );
    auto takeStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { totalTakeNumChars, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { takeStringMalloc, loadedPointerToString, takeSize }
    );

    // append terminator char
    auto pointerToTerminatorPosition = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, takeStringMalloc, { takeSize });
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), pointerToTerminatorPosition, successorBlock, charType);

    auto arrayPointerAllocationForTake = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            totalTakeNumChars,
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