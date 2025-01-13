//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* LambdaIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_EXPRESSION_NODE)) {
        return this->inject((IRLambdaExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->inject((IRLambdaWithFatArrowExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("LambdaIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto functionIndex = irBlock->getBuilder()->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex());
    auto functionPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionIndex });
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), functionPointer);
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = irBlock->getBuilder()->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex());
        auto functionArgumentPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionArgumentIndex });
        auto lambdaScopeAllocation = irBlock->getBuilder()->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
            auto index = irBlock->getBuilder()->get()->getInt32(i);
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto allocationForKey = scope->find(key).value();
            auto pointer = irBlock->getBuilder()->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
            irBlock->getBuilder()->get()->CreateStore(allocationForKey->getValue(), pointer);
        }
        irBlock->getBuilder()->get()->CreateStore(lambdaScopeAllocation, functionArgumentPointer);
    }
    return irBlock->getBuilder()->get()->CreateLoad(allocation->getAllocatedType(), allocation);
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaWithFatArrowExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto functionIndex = irBlock->getBuilder()->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex());
    auto functionPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionIndex });
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), functionPointer);
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = irBlock->getBuilder()->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex());
        auto functionArgumentPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionArgumentIndex });
        auto lambdaScopeAllocation = irBlock->getBuilder()->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
            auto index = irBlock->getBuilder()->get()->getInt32(i);
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto allocationForKey = scope->find(key).value();
            auto pointer = irBlock->getBuilder()->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
            irBlock->getBuilder()->get()->CreateStore(allocationForKey->getValue(), pointer);
        }
        irBlock->getBuilder()->get()->CreateStore(lambdaScopeAllocation, functionArgumentPointer);
    }
    return irBlock->getBuilder()->get()->CreateLoad(allocation->getAllocatedType(), allocation);
}