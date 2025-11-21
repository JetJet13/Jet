//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

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
            auto allocationForKey = scope->find(key).value();
            auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, i);
            InstructionIRInjectorHelper::injectStore(allocationForKey->getValue(), pointer, irBlock, allocationForKey->getIRType()->getUnderlyingType());
        }
        auto lambdaScopeMalloc = irBlock->getBuilder()->get()->CreateCall(
                irModule->getMallocFunction(),
                { irBlock->getBuilder()->get()->getInt64(irExpression->getIRType()->getLambdaVariableType()->getSizeInBytes()) }
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
            auto allocationForKey = scope->find(key).value();
            auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, i);
            InstructionIRInjectorHelper::injectStore(allocationForKey->getValue(), pointer, irBlock, allocationForKey->getIRType()->getUnderlyingType());
        }
        auto lambdaScopeMalloc = irBlock->getBuilder()->get()->CreateCall(
                irModule->getMallocFunction(),
                { irBlock->getBuilder()->get()->getInt64(irExpression->getIRType()->getLambdaVariableType()->getSizeInBytes()) }
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
    return InstructionIRInjectorHelper::injectLoad(allocation->getAllocatedType(), allocation, irBlock);
}