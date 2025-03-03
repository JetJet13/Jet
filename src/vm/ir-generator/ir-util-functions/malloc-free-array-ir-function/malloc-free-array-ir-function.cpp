//
// Created by Johny Georges on 2025-03-03.
//

#include "malloc-free-array-ir-function.h"

std::string MallocFreeArrayIRFunction::getMallocFreeArrayIRFunctionName() {
    return "jet.malloc.free.array";
}

void MallocFreeArrayIRFunction::generateMallocFreeArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto mallocArrayType = irGenerator->generateIrMallocArrayType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(mallocArrayType);
    auto pointerType = irGenerator->generatePointerType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto levelIndex = irGenerator->generateIntConstant(0);
    auto arrayIndex = irGenerator->generateIntConstant(1);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto firstElementIndex = irGenerator->generateIntConstant(arrayPointerType->getPointerIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { intType, pointerType }, false);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocFreeArrayIRFunction::getMallocFreeArrayIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto levels = function->getArg(0);
    auto pointerToRootArray = functionBlock->getBuilder()->get()->CreateAlloca(pointerType);
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), pointerToRootArray);
    auto loadedRootArray = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), pointerToRootArray);
    auto mallocRootArray = functionBlock->getBuilder()->get()->CreateAlloca(mallocArrayType->getType());
    auto levelPointerForMallocRootArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(mallocRootArray->getAllocatedType(), mallocRootArray, { zeroIndex, levelIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), levelPointerForMallocRootArray);
    auto arrayPointerForMallocRootArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(mallocRootArray->getAllocatedType(), mallocRootArray, { zeroIndex, arrayIndex });
    functionBlock->getBuilder()->get()->CreateStore(loadedRootArray, arrayPointerForMallocRootArray);

    // create queue
    auto queueMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { irGenerator->generateIntConstant(mallocArrayType->getSizeInBytes())  });
    auto queueMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(queueMalloc, mallocArrayType->getType());
    auto loadedMallocRootArray = functionBlock->getBuilder()->get()->CreateLoad(mallocRootArray->getAllocatedType(), mallocRootArray);
    functionBlock->getBuilder()->get()->CreateStore(loadedMallocRootArray, queueMallocBitCast);
    auto queue = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType(), nullptr, "queue");
    auto numElementsPointerForQueue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(queue->getAllocatedType(), queue, { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), numElementsPointerForQueue);
    auto firstElementPointerForQueue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(queue->getAllocatedType(), queue, { zeroIndex, firstElementIndex });
    auto firstElementInQueue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(mallocArrayType->getType(), queueMallocBitCast, { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(firstElementInQueue, firstElementPointerForQueue);
    auto allocPointerForQueue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(queue->getAllocatedType(), queue, { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(queueMallocBitCast, allocPointerForQueue);

    // create stack
    auto stackMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction()->getFunctionType(),
            irModuleNode->getMallocFunction(),
            { irGenerator->generateIntConstant(arrayPointerType->getSizeInBytes())  });
    auto stackMallocBitCast = functionBlock->getBuilder()->get()->CreateBitCast(stackMalloc, arrayPointerType->getType());
    functionBlock->getBuilder()->get()->CreateStore(loadedRootArray, queueMalloc);
    auto stack = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType(), nullptr, "stack");
    auto numElementsPointerForStack = functionBlock->getBuilder()->get()->CreateInBoundsGEP(stack->getAllocatedType(), stack, { zeroIndex, numElementsIndex });
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), numElementsPointerForStack);
    auto firstElementPointerForStack = functionBlock->getBuilder()->get()->CreateInBoundsGEP(stack->getAllocatedType(), stack, { zeroIndex, firstElementIndex });
    auto firstElementInStack = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), stackMallocBitCast, { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateStore(firstElementInStack, firstElementPointerForStack);
    auto allocPointerForStack = functionBlock->getBuilder()->get()->CreateInBoundsGEP(stack->getAllocatedType(), stack, { zeroIndex, allocIndex });
    functionBlock->getBuilder()->get()->CreateStore(stackMallocBitCast, allocPointerForStack);

    // stack counter
    auto stackCounter = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "stackCounter");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(1), stackCounter);

    // current level counter
    auto currentLevel = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "currentLevel");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), currentLevel);

    // while loop
    auto whileLoopConditionBlock = irGenerator->generateWhileConditionBlock(irContext);
    auto whileLoopBodyBlock = irGenerator->generateWhileBodyBlock(irContext);
    auto whileLoopEndBlock = irGenerator->generateWhileEndBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(whileLoopConditionBlock->getBlock());

    // while condition block
    auto currentLevelValue = whileLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, currentLevel);
    auto isCurrentLevelLessThanLevels = whileLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            currentLevelValue,
            levels
    );
    auto loadedNumQueueElements = whileLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, numElementsPointerForQueue);
    auto isQueueNotEmpty = whileLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            loadedNumQueueElements,
            irGenerator->generateIntConstant(0)
    );
    auto whileCondition = whileLoopConditionBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isCurrentLevelLessThanLevels,
            isQueueNotEmpty
    );
    whileLoopConditionBlock->getBuilder()->get()->CreateCondBr(whileCondition, whileLoopBodyBlock->getBlock(), whileLoopEndBlock->getBlock());

    // while body block
    auto whileBody = whileLoopBodyBlock->getBuilder()->get();
    auto nodePointer = whileBody->CreateInBoundsGEP(arrayPointerType->getType(), queue, { zeroIndex, firstElementIndex });
    auto loadedNode = whileBody->CreateLoad(mallocArrayType->getType(), nodePointer);
    whileBody->CreateCall(
            irModuleNode->getMallocArrayPopFunction()->getFunctionType(),
            irModuleNode->getMallocArrayPopFunction(),
            { queue }
    );
    auto nodeLevelPointer = whileBody->CreateInBoundsGEP(mallocArrayType->getType(), loadedNode, { zeroIndex, levelIndex });
    auto loadedNodeLevel = whileBody->CreateLoad(intType, nodeLevelPointer);
    whileBody->CreateStore(loadedNodeLevel, currentLevel);
    auto nodeArrayPointer = whileBody->CreateInBoundsGEP(mallocArrayType->getType(), loadedNode, { zeroIndex, arrayIndex });
    auto loadedNodeArray = whileBody->CreateLoad(arrayPointerType->getType(), nodeArrayPointer);
    auto nodeArrayNumElementsPointer = whileBody->CreateInBoundsGEP(arrayPointerType->getType(), loadedNodeArray, { zeroIndex, numElementsIndex });
    auto loadedNodeArrayNumElements = whileBody->CreateLoad(intType, nodeArrayNumElementsPointer);
    auto forLoopIndex = whileBody->CreateAlloca(intType, nullptr, "forLoopIndex");
    whileBody->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);

    // for loop (inside while block)
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    whileBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition (inside while block)
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            loadedNodeArrayNumElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body (inside while block)
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto arrayElementPointer = forLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), loadedNodeArray, { zeroIndex, firstElementIndex, forLoopIndexValue });
    auto loadedArrayElement = forLoopBody->CreateLoad(arrayPointerType->getType(), arrayElementPointer, "arrayElement");
    auto arrayElementLevel = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, loadedNodeLevel, irGenerator->generateIntConstant(1), "arrayElementLevel");
    auto newNode = forLoopBody->CreateAlloca(mallocArrayType->getType(), nullptr, "newNode");
    auto levelPointerForNewNode = forLoopBody->CreateInBoundsGEP(newNode->getAllocatedType(), newNode, { zeroIndex, levelIndex });
    forLoopBody->CreateStore(arrayElementLevel, levelPointerForNewNode);
    auto arrayPointerForNewNode = forLoopBody->CreateInBoundsGEP(newNode->getAllocatedType(), newNode, { zeroIndex, arrayIndex });
    forLoopBody->CreateStore(loadedArrayElement, arrayPointerForNewNode);
    forLoopBody->CreateCall(
            irModuleNode->getMallocArrayEnqueueFunction()->getFunctionType(),
            irModuleNode->getMallocArrayEnqueueFunction(),
            { queue, newNode }
    );
    forLoopBody->CreateCall(
            irModuleNode->getMallocArrayPushFunction()->getFunctionType(),
            irModuleNode->getMallocArrayPushFunction(),
            { stack, arrayElementPointer }
    );
    auto currentStackCounter = forLoopBody->CreateLoad(intType, stackCounter);
    auto newStackCounter = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentStackCounter, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(newStackCounter, stackCounter);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    forLoopBody->CreateStore(forLoopIndex, newForLoopIndexValue);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end (inside while block)
    forLoopEndBlock->getBuilder()->get()->CreateBr(whileLoopConditionBlock->getBlock());

    // intermediate block (in-between while loop and stack for loop)
    auto intermediateBlock = irGenerator->generateBasicBlock("intermediate", irContext);
    whileLoopEndBlock->getBuilder()->get()->CreateBr(intermediateBlock->getBlock());

    auto stackForLoopIndex = intermediateBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "stackForLoopIndex");
    intermediateBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), stackForLoopIndex);
    auto stackCounterValue = intermediateBlock->getBuilder()->get()->CreateLoad(intType, stackCounter);

    // for loop (for stack)
    auto stackForLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto stackForLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto stackForLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    intermediateBlock->getBuilder()->get()->CreateBr(stackForLoopConditionBlock->getBlock());


    // stack for loop condition
    auto stackForLoopIndexValue = stackForLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, stackForLoopIndex);
    auto isStackForLoopIndexLessThanStackCounter = stackForLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            stackForLoopIndexValue,
            stackCounterValue
    );
    stackForLoopConditionBlock->getBuilder()->get()->CreateCondBr(isStackForLoopIndexLessThanStackCounter, stackForLoopBodyBlock->getBlock(), stackForLoopEndBlock->getBlock());

    // stack for loop body
    auto stackForLoopBody = stackForLoopBodyBlock->getBuilder()->get();
    auto stackElementPointer = stackForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), stack, { zeroIndex, firstElementIndex, stackForLoopIndexValue });
    auto loadedStackElement = stackForLoopBody->CreateLoad(arrayPointerType->getType(), stackElementPointer, "stackArrayElement");
    stackForLoopBody->CreateCall(
            irModuleNode->getMallocArrayPopFunction()->getFunctionType(),
            irModuleNode->getMallocArrayPopFunction(),
            { stack }
    );
    auto stackElementAllocPointer = stackForLoopBody->CreateInBoundsGEP(arrayPointerType->getType(), loadedStackElement, { zeroIndex, allocIndex });
    stackForLoopBody->CreateCall(
            irModuleNode->getMallocFreeFunction()->getFunctionType(),
            irModuleNode->getMallocFreeFunction(),
            { stackElementAllocPointer }
    );
    auto newStackForLoopIndexValue = stackForLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, stackForLoopIndexValue, irGenerator->generateIntConstant(1));
    stackForLoopBody->CreateStore(stackForLoopIndex, newStackForLoopIndexValue);
    stackForLoopBody->CreateBr(stackForLoopConditionBlock->getBlock());

    // stack for loop end
    stackForLoopEndBlock->addVoidReturn();
}