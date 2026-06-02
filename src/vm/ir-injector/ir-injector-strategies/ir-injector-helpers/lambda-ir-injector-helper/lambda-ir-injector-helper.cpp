//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-captured-variable-type.h"

llvm::Value* LambdaIRInjectorHelper::injectDetails(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getAllocation(), irBlock);
    auto functionIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex();
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getAllocation()->getAllocatedType(), allocation, functionIndex);
    InstructionIRInjectorHelper::injectStore(irExpression->getFunctionValue(), functionPointer, irBlock, irExpression->getIRType()->getLambdaVariableType());
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex();
        auto functionArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getAllocation()->getAllocatedType(), allocation, functionArgumentIndex);
        auto lambdaScopeAllocation = irBlock->getBuilder()->get()->CreateAlloca(irLambdaScopeType->getType());
        for (unsigned long i = 0; i < irLambdaScopeType->size(); ++i) {
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto irCapturedVariableType = (IRCapturedVariableType*)irLambdaScopeType->getIRTypeForKey(key);
            auto allocationForKey = scope->find(key).value();
            auto allocationCaptureCounterForKey = scope->findArc(key).value();
            auto capturedVariableAllocation = irBlock->getBuilder()->get()->CreateAlloca(irCapturedVariableType->getType());
            auto pointerToCapturedVariable = irBlock->getBuilder()->get()->CreateStructGEP(irCapturedVariableType->getType(), capturedVariableAllocation, irCapturedVariableType->getVariableIndex());
            InstructionIRInjectorHelper::injectStore(allocationForKey->getValue(), pointerToCapturedVariable, irBlock, allocationForKey->getIRType()->getUnderlyingType());
            auto pointerToCaptureCounter = irBlock->getBuilder()->get()->CreateStructGEP(irCapturedVariableType->getType(), capturedVariableAllocation, irCapturedVariableType->getCaptureCounterIndex());
            InstructionIRInjectorHelper::injectStore(allocationCaptureCounterForKey->getValue(), pointerToCaptureCounter, irBlock, allocationCaptureCounterForKey->getIRType());
            auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, i);
            auto loadedCapturedVariableAllocation = InstructionIRInjectorHelper::injectLoad(capturedVariableAllocation->getAllocatedType(), capturedVariableAllocation, irBlock);
            InstructionIRInjectorHelper::injectStore(loadedCapturedVariableAllocation, pointer, irBlock, irCapturedVariableType);
        }
        auto lambdaScopeMalloc = irBlock->getBuilder()->get()->CreateCall(
                irModule->getMallocFunction(),
                {
                        irBlock->getBuilder()->get()->getInt64(1),
                        irBlock->getBuilder()->get()->getInt64(irLambdaScopeType->getSizeInBytes()),
                }
        );
        irBlock->getBuilder()->get()->CreateMemCpy(
                lambdaScopeMalloc,
                irLambdaScopeType->getAlignment(),
                lambdaScopeAllocation,
                irLambdaScopeType->getAlignment(),
                irLambdaScopeType->getSizeInBytes()
        );
        InstructionIRInjectorHelper::injectStore(lambdaScopeMalloc, functionArgumentPointer, irBlock);
    }
    auto refCounterIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionRefCounterIndex();
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getAllocation()->getAllocatedType(), allocation, refCounterIndex);
    auto refCounterAlloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                    irBlock->getBuilder()->get()->getInt64(1),
                    irBlock->getBuilder()->get()->getInt64(irExpression->getIRType()->getLambdaVariableType()->getRefCounterSizeInBytes()),
            }
    );
    auto refCounterValue = irBlock->getBuilder()->get()->getInt64(1);
    InstructionIRInjectorHelper::injectStore(refCounterValue, refCounterAlloc, irBlock);
    InstructionIRInjectorHelper::injectStore(refCounterAlloc, refCounterPointer, irBlock);

    auto lambdaCleanupIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionCleanupIndex();
    auto lambdaCleanupPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getAllocation()->getAllocatedType(), allocation, lambdaCleanupIndex);
    auto lambdaCleanupFunction = irExpression->getCleanupFunction();
    InstructionIRInjectorHelper::injectStore(lambdaCleanupFunction, lambdaCleanupPointer, irBlock);

    auto isPerpetualIndex = irExpression->getIRType()->getLambdaVariableType()->getIsPerpetualIndex();
    auto isPerpetualPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getAllocation()->getAllocatedType(), allocation, isPerpetualIndex);
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getFalse(), isPerpetualPointer, irBlock);

    return InstructionIRInjectorHelper::injectLoad(irExpression->getAllocation()->getAllocatedType(), allocation, irBlock);
}