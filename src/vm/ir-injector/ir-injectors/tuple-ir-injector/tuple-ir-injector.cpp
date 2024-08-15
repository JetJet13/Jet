//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* TupleIRInjector::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->inject((IRTupleExpressionNode*)irExpression, builder);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder);
    }
    throw std::logic_error("StructIRInjector - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* TupleIRInjector::inject(IRTupleExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto tupleExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(tupleExpressionAllocation->getType(), tupleExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irExpression->getValues()->at(i)->insertSelfIntoBlock(builder, _irInjectorMap);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return tupleExpressionAllocation;
}

llvm::Value* TupleIRInjector::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}