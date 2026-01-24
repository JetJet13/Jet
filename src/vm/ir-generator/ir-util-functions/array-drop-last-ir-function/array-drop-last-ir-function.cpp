//
// Created by Johny Georges on 2025-06-05.
//

#include "array-drop-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayDropLastIRFunction::getArrayDropLastIRFunctionName() {
    return "jet.array.drop.last";
}

void ArrayDropLastIRFunction::generateArrayDropLastFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType(), typeValueType->getType() },
                                                false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayDropLastIRFunction::getArrayDropLastIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext);
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
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNewNumElements,
                sizeInBytes
            }
    );
    auto oldArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction()->getFunctionType(),
            irModuleNode->getMallocSizeFunction(),
            {
                    oldNumElements,
                    sizeInBytes
            }
    );
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { loadedNewNumElements, sizeInBytes }
    );
    auto pointerToOldArray = successorBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedPointerToOldArray = successorBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToOldArray);
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction()->getFunctionType(),
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, loadedPointerToOldArray, newArraySize }
    );

    auto arrayPointerAllocationForOldArray = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())
            }
    );
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
    successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeArrayFunction()->getFunctionType(),
            irModuleNode->getFreeArrayFunction(),
            { arrayPointerAllocationForOldArray, function->getArg(2) }
    );
    successorBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}