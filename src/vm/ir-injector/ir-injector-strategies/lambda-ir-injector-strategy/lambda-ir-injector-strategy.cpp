//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-type/ir-captured-variable-type.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

llvm::Value* LambdaIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE)) {
        return this->inject((IRLambdaWithBlockExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->inject((IRLambdaWithFatArrowExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRObjectAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRTupleAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_objectAccessExpressionInjector.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleAccessExpressionInjector.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayAccessExpressionInjector.inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("LambdaIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irExpression->getValue() });
    }

    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }

    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaWithBlockExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto lambdaScope = irExpression->getBlock()->getScope();

    auto lambdaScopeParameter = irExpression->getParameters()->getLambdaScopeParameter();
    if (lambdaScopeParameter) {
        InstructionIRInjectorHelper::inject(lambdaScopeParameter.value()->getAllocation(), irExpression->getBlock());
    }
    irInjector->inject(irBlock, irExpression->getBlock(), irModule);
    if (irExpression->getFunctionValue()->getReturnType()->isVoidTy()) {
        irExpression->getBlock()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(irExpression->getBlock(), irInjector, irModule, lambdaScope);
    FreeIRInjectorHelper::freeFunctionParameters(irExpression->getBlock(), irExpression->getParameters(), irInjector, irModule, lambdaScope);
    DebugIRInjectorHelper::injectFunctionEnterLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    auto value = this->injectDetails(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isOperandPointer()) {
        return irExpression->getAllocation()->getValue();
    }
    return value;
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaWithFatArrowExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto lambdaScope = irExpression->getBlock()->getScope();
    auto lambdaScopeParameter = irExpression->getParameters()->getLambdaScopeParameter();
    if (lambdaScopeParameter) {
        InstructionIRInjectorHelper::inject(lambdaScopeParameter.value()->getAllocation(), irExpression->getBlock());
    }
    irInjector->inject(irBlock, irExpression->getBlock(), irModule);
    auto irReturnExpressionValue = irInjector->inject(irExpression->getBlock(), irExpression->getReturnExpression(), new IROperation(IR_FUNCTION_RETURN_OP), irModule, lambdaScope);
    irExpression->getBlock()->getBuilder()->get()->CreateRet(irReturnExpressionValue);
    FreeIRInjectorHelper::freeFunctionParameters(irExpression->getBlock(), irExpression->getParameters(), irInjector, irModule, lambdaScope);
    DebugIRInjectorHelper::injectFunctionEnterLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    auto value = this->injectDetails(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isOperandPointer()) {
        return irExpression->getAllocation()->getValue();
    }
    return value;
}

llvm::Value* LambdaIRInjectorStrategy::injectDetails(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
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
    return InstructionIRInjectorHelper::injectLoad(irExpression->getAllocation()->getAllocatedType(), allocation, irBlock);
}