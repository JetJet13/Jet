//
// Created by Johny Georges on 2024-08-14.
//

#include "struct-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

llvm::Value* StructIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    if (irExpression->is(IR_STRUCT_EXPRESSION_NODE)) {
        return this->inject((IRStructExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StructIRInjectorStrategy::inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    auto structExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getSourceAllocation().value()->getAllocatedType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())->inject(irExpressionAtIndex, builder, irInjectorMap);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return structExpressionAllocation;
}

llvm::Value* StructIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}