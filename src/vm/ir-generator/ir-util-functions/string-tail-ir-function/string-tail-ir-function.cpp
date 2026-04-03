//
// Created by Johny Georges on 2026-03-23.
//

#include "string-tail-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string StringTailIRFunction::getStringTailIRFunctionName() {
    return "jet.string.tail";
}

void StringTailIRFunction::generateStringTailFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(), { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringTailIRFunction::getStringTailIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isStringEmptyIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isStringEmptyIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getDepthIndex());
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto numChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numCharsPointer);
    functionBlock->getBuilder()->get()->CreateBr(isStringEmptyIfBlock->getBlock());

    // isStringEmptyIfBlock
    auto isStringEmpty = isStringEmptyIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            numChars,
            irGenerator->generateIntConstant(1)
    );
    isStringEmptyIfBlock->getBuilder()->get()->CreateCondBr(isStringEmpty, isStringEmptyIfThenBlock->getBlock(), successorBlock->getBlock());

    // isStringEmptyIfThenBlock
    auto emptyTailStringMalloc = isStringEmptyIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(1), sizeInBytes }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), emptyTailStringMalloc, isStringEmptyIfThenBlock, charType);
    auto arrayPointerAllocationForEmptyTail = isStringEmptyIfThenBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            isStringEmptyIfThenBlock,
            arrayPointerType,
            irGenerator->generateIntConstant(1),
            depth,
            arrayPointerAllocationForEmptyTail,
            emptyTailStringMalloc
    );
    auto loadedEmptyTail = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForEmptyTail, isStringEmptyIfThenBlock, arrayPointerType);
    isStringEmptyIfThenBlock->getBuilder()->get()->CreateRet(loadedEmptyTail);

    auto tailNumChars = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, numChars, irGenerator->generateIntConstant(1));
    auto tailStringSize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                tailNumChars,
                sizeInBytes
            }
    );
    auto tailStringMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { tailNumChars, sizeInBytes }
    );
    auto pointerToString = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToString = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    auto secondElementPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToString, { sizeInBytes });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { tailStringMalloc, secondElementPointer, tailStringSize }
    );
    auto arrayPointerAllocationForTail = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            tailNumChars,
            depth,
            arrayPointerAllocationForTail,
            tailStringMalloc
    );
    auto arrayPointerAllocationForTailCopy = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyStringFunction(),
            { arrayPointerAllocationForTailCopy, arrayPointerAllocationForTail }
    );
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeStringFunction(),
            { arrayPointerAllocationForTail }
    );
    auto loadedTail = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), arrayPointerAllocationForTailCopy, successorBlock, arrayPointerType);
    successorBlock->getBuilder()->get()->CreateRet(loadedTail);
}