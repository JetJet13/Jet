//
// Created by Johny Georges on 2024-08-14.
//

#include "struct-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* StructIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    if (irExpression->is(IR_STRUCT_EXPRESSION_NODE)) {
        return this->inject((IRStructExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StructIRInjectorStrategy::inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    auto structExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())->inject(irExpressionAtIndex, builder, irInjectorMap, irOperationType);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return builder->get()->CreateLoad(structExpressionAllocation->getType(), structExpressionAllocation);
}

llvm::Value* StructIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    auto structAllocation = irExpression->getSourceAllocation().value()->getParentAllocation().value();
    auto destinationAllocation = IRInstructionNodeFactory::create(structAllocation);
    builder->get()->Insert(destinationAllocation->getValue());
    auto irStructType = (IRStructType*)structAllocation->getIRType()->getSourceType();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto index = builder->get()->getInt32(i);
        auto destinationPointer = builder->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), { zeroIndex, index });
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerAllocation);
            builder->get()->CreateStore(loadedArrayPointer->getValue(), destinationPointer);
        } else {
            auto elementPointer = builder->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
            auto loadedValue = builder->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
            builder->get()->CreateStore(loadedValue, destinationPointer);
        }
    }
    return builder->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue());
}