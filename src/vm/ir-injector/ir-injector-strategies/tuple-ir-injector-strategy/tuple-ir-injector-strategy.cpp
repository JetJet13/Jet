//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

llvm::Value* TupleIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->inject((IRTupleExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* TupleIRInjectorStrategy::inject(IRTupleExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    auto tupleExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(tupleExpressionAllocation->getType(), tupleExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())->inject(irExpressionAtIndex, builder, irInjectorMap, irOperationType);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return tupleExpressionAllocation;
}

llvm::Value* TupleIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}