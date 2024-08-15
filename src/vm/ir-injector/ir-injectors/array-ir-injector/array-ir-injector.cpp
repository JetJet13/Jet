//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRInjector::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (irExpression->is(IR_ARRAY_EXPRESSION_NODE)) {
        return this->inject((IRArrayExpressionNode*)irExpression, builder);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder);
    }
    throw std::logic_error("ArrayIRInjector - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* ArrayIRInjector::inject(IRArrayExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->Insert(irExpression->getSourceArrayAllocation()->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getSourceArrayAllocation()->getAllocatedType(), irExpression->getSourceArrayAllocation()->getValue(), { zeroIndex, irIndex });
        auto irExpressionValue = elementExpression->insertSelfIntoBlock(builder, _irInjectorMap);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), irExpression->getArrayPointerAllocation());
}

llvm::Value* ArrayIRInjector::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder);
}
