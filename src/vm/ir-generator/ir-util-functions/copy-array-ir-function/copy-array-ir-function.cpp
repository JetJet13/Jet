//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-array-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

std::string CopyArrayIRFunction::getCopyArrayIRFunctionName() {
    return "jet.copy.array";
}

void CopyArrayIRFunction::generateCopyArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto arrayIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irGenerator->generateIntConstant(arrayPointerType->getDepthIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType }, false);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyArrayIRFunction::getCopyArrayIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto pointerToSourceArray = functionBlock->getBuilder()->get()->CreateAlloca(pointerType);
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(0), pointerToSourceArray);
    auto loadedSourceArray = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), pointerToSourceArray);
    auto pointerToSourceArrayNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), loadedSourceArray, { zeroIndex, numElementsIndex });
    auto sourceArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayNumElements);
    auto pointerToSourceArrayDepth = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), loadedSourceArray, { zeroIndex, depthIndex });
    auto sourceArrayDepth = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToSourceArrayDepth);
    auto destinationArrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    auto destinationArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(sourceArrayNumElements, destinationArrayNumElementsPointer);
    auto destinationArrayDepthPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, depthIndex });
    functionBlock->getBuilder()->get()->CreateStore(sourceArrayDepth, destinationArrayDepthPointer);
    auto destinationArrayAllocPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), destinationArrayPointerAllocation, { zeroIndex, allocIndex });

    auto mallocSize = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocSizeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocSizeFunction(),
            {
                    sourceArrayNumElements,
                    irGenerator->generateIntConstant(arrayPointerType->getElementIRType()->getSizeInBytes())
            },
            ""
    );
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { mallocSize },
            ""
    );

    auto depthOneBlock = irGenerator->generateIfThenBlock(irContext);
    auto sourceArrayAllocation = depthOneBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), loadedSourceArray, { zeroIndex, allocIndex });
    // todo: to perform a proper copy, we need to know what type of the array element type is
    // because that will decide how to copy. we'll need to represent types as values and then
    // add a new parameter to this function that will indicate what the type is.
    // We'll also need a parameter to determine the alignment
    depthOneBlock->getBuilder()->get()->CreateMemCpy(
            sourceArrayAllocation,
            llvm::Align(4), // fixme
            malloc,
            llvm::Align(4),
            mallocSize
    );
    depthOneBlock->getBuilder()->get()->CreateStore(malloc, destinationArrayAllocPointer);
    depthOneBlock->getBuilder()->get()->CreateRet(
            depthOneBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationArrayPointerAllocation)
    );

    auto functionLoopPrepBlock = irGenerator->generateBasicBlock("", irContext);
    auto functionLoopEndBlock = irGenerator->generateBasicBlock("", irContext);
    auto isDepthOne = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            sourceArrayDepth,
            irGenerator->generateIntConstant(1)
    );
    functionBlock->getBuilder()->get()->CreateCondBr(isDepthOne, depthOneBlock->getBlock(), functionLoopPrepBlock->getBlock());


    auto destinationArray = functionLoopPrepBlock->getBuilder()->get()->CreateBitCast(malloc, arrayPointerType->getType());
    functionLoopPrepBlock->getBuilder()->get()->CreateStore(destinationArray, destinationArrayAllocPointer);

    auto forLoopIndex = functionLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    functionLoopPrepBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop (inside while block)
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    functionLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition (inside while block)
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            sourceArrayNumElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body (inside while block)
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto arrayElementPointer = forLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), loadedSourceArray, { zeroIndex, allocIndex, forLoopIndexValue }, "arrayElement");
    auto copiedArrayElement = forLoopBody->CreateCall(
            irModuleNode->getCopyArrayFunction()->getFunctionType(),
            irModuleNode->getCopyArrayFunction(),
            { arrayElementPointer }
    );
    auto destinationArrayElementPointer = forLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), destinationArray, { zeroIndex, forLoopIndexValue });
    forLoopBody->CreateStore(copiedArrayElement, destinationArrayElementPointer);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(forLoopIndex, newForLoopIndexValue);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end (inside while block)
    forLoopEndBlock->getBuilder()->get()->CreateBr(functionLoopEndBlock->getBlock());

    functionLoopEndBlock->getBuilder()->get()->CreateRet(
        functionLoopEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), destinationArrayPointerAllocation)
    );
}