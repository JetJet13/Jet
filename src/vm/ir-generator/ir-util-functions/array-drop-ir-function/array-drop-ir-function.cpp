//
// Created by Johny Georges on 2025-06-02.
//

#include "array-drop-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayDropIRFunction::getArrayDropIRFunctionName() {
    return "jet.array.drop";
}

void ArrayDropIRFunction::generateArrayDropFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
        { pointerType->getType(), pointerType->getType(), typeValueType->getType() },
        false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayDropIRFunction::getArrayDropIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    functionBlock->createSuccessor();
    auto successorBlock = functionBlock->getLastSuccessorOrSelf();
    auto numElementsIndex = arrayPointerType->getNumElementsIndex();
    auto allocIndex = arrayPointerType->getAllocIndex();
    auto depthIndex = arrayPointerType->getDepthIndex();
    auto sizeInBytesIndex = typeValueType->getSizeInBytesIndex();
    auto arrayElementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "arrayElementTypeValue");
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValue, sizeInBytesIndex);
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, arrayElementSizeInBytesPointer, "sizeInBytes");
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), depthIndex);
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);
    auto numElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), numElementsIndex);
    auto numElementsToDrop = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    auto oldNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointer);
    auto newNumElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto newNumElements = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumElements, numElementsToDrop);
    functionBlock->getBuilder()->get()->CreateStore(newNumElements, newNumElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            newNumElements,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), newNumElementsAllocation);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateBr(successorBlock->getBlock());

    auto loadedNewNumElements = successorBlock->getBuilder()->get()->CreateLoad(intType, newNumElementsAllocation, "newNumElements");
    auto newArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNewNumElements,
                sizeInBytes
            }
    );
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { newArraySize }
    );
    auto oldArrayOffset = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, sizeInBytes, numElementsToDrop);
    auto pointerToOldArray = successorBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), allocIndex);
    auto loadedPointerToOldArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    auto oldArrayOffsetPointer = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedPointerToOldArray, { oldArrayOffset });
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, oldArrayOffsetPointer, newArraySize }
    );

    auto arrayPointerAllocationForOldArray = successorBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            successorBlock,
            arrayPointerType,
            oldNumElements,
            depth,
            arrayPointerAllocationForOldArray,
            loadedPointerToOldArray
    );
    successorBlock->getBuilder()->get()->CreateStore(loadedNewNumElements, numElementsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToOldArray);
//    successorBlock->getBuilder()->get()->CreateCall(
//        irModuleNode->getFreeArrayFunction(),
//        { arrayPointerAllocationForOldArray, function->getArg(2) }
//    );
    successorBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}