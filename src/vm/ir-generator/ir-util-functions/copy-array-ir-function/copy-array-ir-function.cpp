//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-array-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string CopyArrayIRFunction::getCopyArrayIRFunctionName() {
    return "jet.copy.array";
}

void CopyArrayIRFunction::declareCopyArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyArrayIRFunction::getCopyArrayIRFunctionName(), irModuleNode->getModule());
}

void CopyArrayIRFunction::generateCopyArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto function = irModuleNode->getCopyArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto pointerToSourceArrayNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, numElementsIndex });
    auto sourceArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayNumElements);
    auto pointerToSourceArrayDepth = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, depthIndex });
    auto sourceArrayDepth = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayDepth);
    auto destinationArrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    auto destinationArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(sourceArrayNumElements, destinationArrayNumElementsPointer);
    auto destinationArrayDepthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, depthIndex });
    functionBlock->getBuilder()->get()->CreateStore(sourceArrayDepth, destinationArrayDepthPointer);
    auto destinationArrayAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, allocIndex });

    auto typeValueSizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());
    auto typeValueAllocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());

    auto pointerToElementTypeValue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(2), { zeroIndex, typeValueAllocIndex });
    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), pointerToElementTypeValue);
    auto pointerToElementTypeValueSizeInBytes = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), elementTypeValue, { zeroIndex, typeValueSizeInBytesIndex });
    auto elementSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToElementTypeValueSizeInBytes, "elementTypeSizeInBytes");
    auto pointerToElementTypeValueId = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), elementTypeValue, { zeroIndex, typeValueIdIndex });
    auto elementTypeValueId = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToElementTypeValueId, "elementTypeId");

    auto mallocSize = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocSizeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocSizeFunction(),
            {
                    sourceArrayNumElements,
                    elementSizeInBytes
            },
            ""
    );
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { mallocSize },
            ""
    );
    functionBlock->getBuilder()->get()->CreateStore(malloc, destinationArrayAllocPointer);

    std::string depthOnePrefix = "depth.1.";
    std::string depthNPrefix = "depth.n.";
    auto depthOneBlock = irGenerator->generateIfThenBlock(irContext, depthOnePrefix);
    auto depthOneTypeLiteralTrueBlock = irGenerator->generateIfThenBlock(irContext, depthOnePrefix + "is.literal.");
    auto depthOneTypeLiteralFalseBlock = irGenerator->generateIfElseBlock(irContext, depthOnePrefix + "is.literal.");
    auto depthOneForLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, depthOnePrefix);
    auto depthOneForLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, depthOnePrefix);
    auto depthOneForLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, depthOnePrefix);
    auto depthOneTypeLiteralEndBlock = irGenerator->generateIfEndBlock(irContext, depthOnePrefix);
    auto depthNForLoopPrepBlock = irGenerator->generateBasicBlock(depthNPrefix + "prep", irContext);
    auto depthNForLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, depthNPrefix);
    auto depthNForLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, depthNPrefix);
    auto depthNForLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, depthNPrefix);

    auto isDepthOne = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            sourceArrayDepth,
            irGenerator->generateIntConstant(1)
    );
    functionBlock->getBuilder()->get()->CreateCondBr(isDepthOne, depthOneBlock->getBlock(), depthNForLoopPrepBlock->getBlock());

    // depth 1 block
    auto sourceArrayAllocationPointer = depthOneBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), { zeroIndex, allocIndex });
    auto loadedSourceArrayAllocation = depthOneBlock->getBuilder()->get()->CreateLoad(pointerType, sourceArrayAllocationPointer);
    auto isElementTypeLiteral = depthOneBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            elementTypeValueId,
            irGenerator->generateIntConstant(5)
    );
    depthOneBlock->getBuilder()->get()->CreateCondBr(isElementTypeLiteral, depthOneTypeLiteralTrueBlock->getBlock(), depthOneTypeLiteralFalseBlock->getBlock());


    depthOneTypeLiteralTrueBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMemcpyFunction()->getFunctionType(),
            irContext->getIRModule()->getMemcpyFunction(),
            {
                    malloc,
                    loadedSourceArrayAllocation,
                    mallocSize
            }
    );
    depthOneTypeLiteralTrueBlock->getBuilder()->get()->CreateBr(depthOneTypeLiteralEndBlock->getBlock());

    auto elementByteOffset = depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto depthOneForLoopIndex = depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "depthOneForLoopIndex");
    depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), depthOneForLoopIndex);

    // depth 1 for loop
    depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateBr(depthOneForLoopConditionBlock->getBlock());
    // depth 1  for loop condition
    auto depthOneForLoopIndexValue = depthOneForLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, depthOneForLoopIndex);
    auto depthOneForLoopIndexLessThanNumElements = depthOneForLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            depthOneForLoopIndexValue,
            sourceArrayNumElements
    );
    depthOneForLoopConditionBlock->getBuilder()->get()->CreateCondBr(depthOneForLoopIndexLessThanNumElements, depthOneForLoopBodyBlock->getBlock(), depthOneForLoopEndBlock->getBlock());

    // depth 1 for loop body
    auto depthOneForLoopBody = depthOneForLoopBodyBlock->getBuilder()->get();
    auto elementByteOffsetValue = depthOneForLoopBody->CreateLoad(intType, elementByteOffset);
    auto destinationPointerAtIndex = depthOneForLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), malloc, {elementByteOffsetValue });
    auto sourcePointerAtIndex = depthOneForLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), loadedSourceArrayAllocation, {elementByteOffsetValue });
    depthOneForLoopBody->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationPointerAtIndex, sourcePointerAtIndex, elementTypeValue }
    );

    auto newElementByteOffsetValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, elementSizeInBytes);
    depthOneForLoopBody->CreateStore(newElementByteOffsetValue, elementByteOffset);

    auto newIsElementTypeLiteralFalseForLoopIndexValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, depthOneForLoopIndexValue, irGenerator->generateIntConstant(1));
    depthOneForLoopBody->CreateStore(newIsElementTypeLiteralFalseForLoopIndexValue, depthOneForLoopIndex);
    depthOneForLoopBody->CreateBr(depthOneForLoopConditionBlock->getBlock());

    // depth 1 for loop end
    depthOneForLoopEndBlock->getBuilder()->get()->CreateBr(depthOneTypeLiteralEndBlock->getBlock());

    // is element type literal end block
    depthOneTypeLiteralEndBlock->getBuilder()->get()->CreateStore(destinationArrayPointerAllocation, function->getArg(0));
    depthOneTypeLiteralEndBlock->addVoidReturn();



    auto destinationArray = depthNForLoopPrepBlock->getBuilder()->get()->CreateBitCast(malloc, arrayPointerType->getType());

    auto forLoopIndex = depthNForLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    depthNForLoopPrepBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // depth N for loop
    depthNForLoopPrepBlock->getBuilder()->get()->CreateBr(depthNForLoopConditionBlock->getBlock());

    // depth N for loop condition
    auto forLoopIndexValue = depthNForLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = depthNForLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            sourceArrayNumElements
    );
    depthNForLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, depthNForLoopBodyBlock->getBlock(), depthNForLoopEndBlock->getBlock());

    // depth N for loop body
    auto depthNForLoopBody = depthNForLoopBodyBlock->getBuilder()->get();
    auto pointerToSourceAlloc = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(1), {zeroIndex, allocIndex });
    auto sourceAlloc = depthNForLoopBody->CreateLoad(pointerType, pointerToSourceAlloc);
    auto pointerToSourceElement = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), sourceAlloc, {forLoopIndexValue });
    auto pointerToDestinationElement = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), destinationArray, {forLoopIndexValue });
    depthNForLoopBody->CreateCall(
            irModuleNode->getCopyArrayFunction()->getFunctionType(),
            irModuleNode->getCopyArrayFunction(),
            { pointerToDestinationElement, pointerToSourceElement, elementTypeValue }
    );
    auto newForLoopIndexValue = depthNForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    depthNForLoopBody->CreateStore(newForLoopIndexValue, forLoopIndex);
    depthNForLoopBody->CreateBr(depthNForLoopConditionBlock->getBlock());

    // depth N for loop end
    depthNForLoopEndBlock->getBuilder()->get()->CreateStore(destinationArrayPointerAllocation, function->getArg(0));
    depthNForLoopEndBlock->addVoidReturn();
}