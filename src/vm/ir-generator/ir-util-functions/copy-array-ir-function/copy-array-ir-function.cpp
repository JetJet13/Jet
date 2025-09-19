//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-array-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

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

    auto function = irModuleNode->getCopyArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto pointerToSourceArrayNumElements = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getNumElementsIndex());
    auto sourceArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayNumElements);
    auto pointerToSourceArrayDepth = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getDepthIndex());
    auto sourceArrayDepth = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayDepth);
    auto destinationArrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    auto destinationArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(sourceArrayNumElements, destinationArrayNumElementsPointer, functionBlock);
    //    functionBlock->getBuilder()->get()->CreateStore(sourceArrayNumElements, destinationArrayNumElementsPointer);
    auto destinationArrayDepthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(sourceArrayDepth, destinationArrayDepthPointer, functionBlock);
    //    functionBlock->getBuilder()->get()->CreateStore(sourceArrayDepth, destinationArrayDepthPointer);
    auto destinationArrayAllocPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, arrayPointerType->getAllocIndex());

    auto elementTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "elementTypeValue");
    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), elementTypeValuePointer);

    auto elementSizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, { typeValueType->getSizeInBytesIndex() }, "elementTypeSizeInBytes");
    auto elementTypeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, { typeValueType->getIdIndex() });

    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintDebugMarkerFunction(), { elementSizeInBytes });
    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintNewLineFunction(),{});

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
    InstructionIRInjectorHelper::injectStore(malloc, destinationArrayAllocPointer, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(malloc, destinationArrayAllocPointer);

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
    auto sourceArrayAllocationPointer = depthOneBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getAllocIndex());
    auto loadedSourceArrayAllocation = depthOneBlock->getBuilder()->get()->CreateLoad(pointerType, sourceArrayAllocationPointer);
    auto isElementTypeLiteral = depthOneBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            elementTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL)
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
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, depthOneTypeLiteralFalseBlock);
//    depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), elementByteOffset);

    auto depthOneForLoopIndex = depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "depthOneForLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), depthOneForLoopIndex, depthOneTypeLiteralFalseBlock);
//    depthOneTypeLiteralFalseBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), depthOneForLoopIndex);

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
    auto elementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, depthOneForLoopBodyBlock);
//    auto elementByteOffsetValue = depthOneForLoopBody->CreateLoad(intType, elementByteOffset);
    depthOneForLoopBody->CreateCall(irModuleNode->getPrintDebugMarkerFunction(), { elementByteOffsetValue });
    depthOneForLoopBody->CreateCall(irModuleNode->getPrintNewLineFunction(),{});
    auto destinationPointerAtIndex = depthOneForLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), malloc, { elementByteOffsetValue });
    auto sourcePointerAtIndex = depthOneForLoopBody->CreateInBoundsGEP(irGenerator->generatePointerIntType(), loadedSourceArrayAllocation, { elementByteOffsetValue });
    depthOneForLoopBody->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationPointerAtIndex, sourcePointerAtIndex, elementTypeValue }
    );

    auto newElementByteOffsetValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, elementSizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, elementByteOffset, depthOneForLoopBodyBlock);
    //    depthOneForLoopBody->CreateStore(newElementByteOffsetValue, elementByteOffset);

    auto newIsElementTypeLiteralFalseForLoopIndexValue = depthOneForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, depthOneForLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newIsElementTypeLiteralFalseForLoopIndexValue, depthOneForLoopIndex, depthOneForLoopBodyBlock);
    //    depthOneForLoopBody->CreateStore(newIsElementTypeLiteralFalseForLoopIndexValue, depthOneForLoopIndex);
    depthOneForLoopBody->CreateBr(depthOneForLoopConditionBlock->getBlock());

    // depth 1 for loop end
    depthOneForLoopEndBlock->getBuilder()->get()->CreateBr(depthOneTypeLiteralEndBlock->getBlock());

    // is element type literal end block
    auto loadedDestinationArrayPointer = depthOneTypeLiteralEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationArrayPointerAllocation);
    InstructionIRInjectorHelper::injectStore(loadedDestinationArrayPointer, function->getArg(0), depthOneTypeLiteralEndBlock);
//    depthOneTypeLiteralEndBlock->getBuilder()->get()->CreateStore(loadedDestinationArrayPointer, function->getArg(0));
    depthOneTypeLiteralEndBlock->addVoidReturn();


    auto destinationArray = depthNForLoopPrepBlock->getBuilder()->get()->CreateBitCast(malloc, arrayPointerType->getType()->getPointerTo());

    auto forLoopIndex = depthNForLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    auto pointerToSourceAlloc = depthNForLoopPrepBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getAllocIndex());
    auto sourceAlloc = depthNForLoopPrepBlock->getBuilder()->get()->CreateLoad(pointerType, pointerToSourceAlloc);
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
    auto pointerToSourceElement = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), sourceAlloc, { forLoopIndexValue });
    auto pointerToDestinationElement = depthNForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), destinationArray, { forLoopIndexValue });
    depthNForLoopBody->CreateCall(
        irModuleNode->getCopyArrayFunction()->getFunctionType(),
        irModuleNode->getCopyArrayFunction(),
        { pointerToDestinationElement, pointerToSourceElement, elementTypeValue }
    );
    auto newForLoopIndexValue = depthNForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    depthNForLoopBody->CreateStore(newForLoopIndexValue, forLoopIndex);
    depthNForLoopBody->CreateBr(depthNForLoopConditionBlock->getBlock());

    // depth N for loop end
    auto loadedDestinationArrayPointerAllocation = depthNForLoopEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationArrayPointerAllocation);
    depthNForLoopEndBlock->getBuilder()->get()->CreateStore(loadedDestinationArrayPointerAllocation, function->getArg(0));
    depthNForLoopEndBlock->addVoidReturn();
}