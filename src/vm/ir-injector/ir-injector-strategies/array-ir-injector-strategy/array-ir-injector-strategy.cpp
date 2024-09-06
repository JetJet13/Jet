//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    if (irExpression->is(IR_ARRAY_EXPRESSION_NODE)) {
        return this->inject((IRArrayExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    }
    throw std::logic_error("ArrayIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRArrayExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    builder->get()->Insert(irExpression->getSourceAggregateAllocation()->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getSourceAggregateAllocation()->getAllocatedType(),
                                                         irExpression->getSourceAggregateAllocation()->getValue(), {zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(elementExpression->getTypeSignature())->inject(elementExpression, builder, irInjectorMap, irOperationType);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation());
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
   return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder);
}
