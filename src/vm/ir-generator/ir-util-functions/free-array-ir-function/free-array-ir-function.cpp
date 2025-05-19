//
// Created by Johny Georges on 2025-05-01.
//

#include "free-array-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../types/ir-type-id.h"

std::string FreeArrayIRFunction::getFreeArrayIRFunctionName() {
    return "jet.free.array";
}

void FreeArrayIRFunction::declareFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeArrayIRFunction::getFreeArrayIRFunctionName(), irModuleNode->getModule());
}

void FreeArrayIRFunction::generateFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto function = irModuleNode->getFreeArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto pointerToSourceArrayNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, numElementsIndex });
    auto sourceArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayNumElements);
    auto pointerToSourceArrayDepth = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, depthIndex });
    auto sourceArrayDepth = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayDepth);

    auto typeValueSizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getAllocIndex() });
    auto pointerToElementTypeValueSizeInBytes = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), elementTypeValue, { zeroIndex, typeValueSizeInBytesIndex });
    auto elementSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToElementTypeValueSizeInBytes, "elementTypeSizeInBytes");
    auto pointerToElementTypeValueId = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), elementTypeValue, { zeroIndex, typeValueIdIndex });
    auto elementTypeValueId = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToElementTypeValueId, "elementTypeId");


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
    auto sourceArrayAllocationPointer = depthOneBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedSourceArrayAllocation = depthOneBlock->getBuilder()->get()->CreateLoad(pointerType, sourceArrayAllocationPointer);
    auto isElementTypeLiteral = depthOneBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            elementTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL)
    );
    depthOneBlock->getBuilder()->get()->CreateCondBr(isElementTypeLiteral, depthOneTypeLiteralTrueBlock->getBlock(), depthOneTypeLiteralFalseBlock->getBlock());


    depthOneTypeLiteralTrueBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFreeFunction(),
            { loadedSourceArrayAllocation }
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
    auto elementPointerAtIndex = depthOneForLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), loadedSourceArrayAllocation, {elementByteOffsetValue });
    auto loadedElementTypeValue = depthOneForLoopBody->CreateLoad(typeValueType->getType(), elementTypeValue);
    depthOneForLoopBody->CreateCall(
            irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeValueFunction(),
            { elementPointerAtIndex, loadedElementTypeValue }
    );
    depthOneForLoopBody->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFreeFunction(),
            { elementPointerAtIndex }
    );

    auto newElementByteOffsetValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, elementSizeInBytes);
    depthOneForLoopBody->CreateStore(newElementByteOffsetValue, elementByteOffset);

    auto newIsElementTypeLiteralFalseForLoopIndexValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, depthOneForLoopIndexValue, irGenerator->generateIntConstant(1));
    depthOneForLoopBody->CreateStore(newIsElementTypeLiteralFalseForLoopIndexValue, depthOneForLoopIndex);
    depthOneForLoopBody->CreateBr(depthOneForLoopConditionBlock->getBlock());

    // depth 1 for loop end
    depthOneForLoopEndBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFreeFunction(),
            { function->getArg(0) }
    );
    depthOneForLoopEndBlock->getBuilder()->get()->CreateBr(depthOneTypeLiteralEndBlock->getBlock());

    // is element type literal end block
    depthOneTypeLiteralEndBlock->addVoidReturn();

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
    auto pointerToSourceAlloc = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), {zeroIndex, allocIndex });
    auto sourceAlloc = depthNForLoopBody->CreateLoad(pointerType, pointerToSourceAlloc);
    auto pointerToElement = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), sourceAlloc, {forLoopIndexValue });
    depthNForLoopBody->CreateCall(
            irModuleNode->getFreeArrayFunction()->getFunctionType(),
            irModuleNode->getFreeArrayFunction(),
            { pointerToElement, elementTypeValue }
    );
    auto newForLoopIndexValue = depthNForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    depthNForLoopBody->CreateStore(newForLoopIndexValue, forLoopIndex);
    depthNForLoopBody->CreateBr(depthNForLoopConditionBlock->getBlock());

    // depth N for loop end
    depthNForLoopEndBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { function->getArg(0) }
    );
    depthNForLoopEndBlock->addVoidReturn();
}