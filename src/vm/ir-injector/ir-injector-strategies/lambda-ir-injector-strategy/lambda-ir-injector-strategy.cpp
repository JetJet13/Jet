//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"

llvm::Value* LambdaIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>* builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_EXPRESSION_NODE)) {
        return this->inject((IRLambdaExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->inject((IRLambdaWithFatArrowExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    }
    throw std::logic_error("LambdaIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>* builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = builder->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto zeroIndex = builder->get()->getInt32(0);
    auto functionIndex = builder->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex());
    auto functionPointer = builder->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionIndex });
    builder->get()->CreateStore(irExpression->getValue(), functionPointer);
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = builder->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex());
        auto functionArgumentPointer = builder->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionArgumentIndex });
        auto lambdaScopeAllocation = builder->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
            auto index = builder->get()->getInt32(i);
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto allocationForKey = scope->find(key).value();
            auto pointer = builder->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
            builder->get()->CreateStore(allocationForKey->getValue(), pointer);
        }
        builder->get()->CreateStore(lambdaScopeAllocation, functionArgumentPointer);
    }
    return builder->get()->CreateLoad(allocation->getAllocatedType(), allocation);
}

llvm::Value* LambdaIRInjectorStrategy::inject(IRLambdaWithFatArrowExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>* builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto allocation = builder->get()->CreateAlloca(irExpression->getIRType()->getLambdaVariableType()->getType());
    auto zeroIndex = builder->get()->getInt32(0);
    auto functionIndex = builder->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionIndex());
    auto functionPointer = builder->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionIndex });
    builder->get()->CreateStore(irExpression->getValue(), functionPointer);
    if (irExpression->getIRType()->getLambdaScopeType()) {
        auto irLambdaScopeType = (IRStructType*)irExpression->getIRType()->getLambdaScopeType().value();
        auto functionArgumentIndex = builder->get()->getInt32(irExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex());
        auto functionArgumentPointer = builder->get()->CreateInBoundsGEP(allocation->getAllocatedType(), allocation, { zeroIndex, functionArgumentIndex });
        auto lambdaScopeAllocation = builder->get()->CreateAlloca(irLambdaScopeType->getType());
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
            auto index = builder->get()->getInt32(i);
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto allocationForKey = scope->find(key).value();
            auto pointer = builder->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
            builder->get()->CreateStore(allocationForKey->getValue(), pointer);
        }
        builder->get()->CreateStore(lambdaScopeAllocation, functionArgumentPointer);
    }
    return builder->get()->CreateLoad(allocation->getAllocatedType(), allocation);
}