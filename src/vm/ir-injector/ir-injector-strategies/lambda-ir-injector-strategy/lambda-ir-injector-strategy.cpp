//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-type/ir-captured-variable-type.h"

llvm::Value* LambdaIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_EXPRESSION_NODE)) {
        return this->inject((IRLambdaExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->inject((IRLambdaWithFatArrowExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRObjectAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("LambdaIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto functionIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex();
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, functionIndex);
    InstructionIRInjectorHelper::injectStore(irExpression->getValue(), functionPointer, irBlock, irExpression->getIRType());
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex();
        auto functionArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, functionArgumentIndex);
        auto lambdaScopeAllocation = irBlock->getBuilder()->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
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
                { irBlock->getBuilder()->get()->getInt64(irLambdaScopeType->getSizeInBytes()) }
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
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, refCounterIndex);
    auto refCounterAlloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            { irBlock->getBuilder()->get()->getInt64(irExpression->getIRType()->getLambdaVariableType()->getRefCounterSizeInBytes()) }
    );
    auto refCounterValue = irBlock->getBuilder()->get()->getInt64(1);
    InstructionIRInjectorHelper::injectStore(refCounterValue, refCounterAlloc, irBlock);
    InstructionIRInjectorHelper::injectStore(refCounterAlloc, refCounterPointer, irBlock);

    auto lambdaCleanupIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionCleanupIndex();
    auto lambdaCleanupPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, lambdaCleanupIndex);
    auto lambdaCleanupFunction = irExpression->getCleanupFunction();
    InstructionIRInjectorHelper::injectStore(lambdaCleanupFunction, lambdaCleanupPointer, irBlock);
    return InstructionIRInjectorHelper::injectLoad(allocation->getAllocatedType(), allocation, irBlock);
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaWithFatArrowExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto functionIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex();
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, functionIndex);
    InstructionIRInjectorHelper::injectStore(irExpression->getValue(), functionPointer, irBlock, irExpression->getIRType()->getLambdaVariableType());
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex();
        auto functionArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, functionArgumentIndex);
        auto lambdaScopeAllocation = irBlock->getBuilder()->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
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
                { irBlock->getBuilder()->get()->getInt64(irLambdaScopeType->getSizeInBytes()) }
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
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, refCounterIndex);
    auto refCounterAlloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            { irBlock->getBuilder()->get()->getInt64(irExpression->getIRType()->getLambdaVariableType()->getRefCounterSizeInBytes()) }
    );
    auto refCounterValue = irBlock->getBuilder()->get()->getInt64(1);
    InstructionIRInjectorHelper::injectStore(refCounterValue, refCounterAlloc, irBlock);
    InstructionIRInjectorHelper::injectStore(refCounterAlloc, refCounterPointer, irBlock);

    auto lambdaCleanupIndex = irExpression->getIRType()->getLambdaVariableType()->getFunctionCleanupIndex();
    auto lambdaCleanupPointer = irBlock->getBuilder()->get()->CreateStructGEP(allocation->getAllocatedType(), allocation, lambdaCleanupIndex);
    auto lambdaCleanupFunction = irExpression->getCleanupFunction();
    InstructionIRInjectorHelper::injectStore(lambdaCleanupFunction, lambdaCleanupPointer, irBlock);
    return InstructionIRInjectorHelper::injectLoad(allocation->getAllocatedType(), allocation, irBlock);
}