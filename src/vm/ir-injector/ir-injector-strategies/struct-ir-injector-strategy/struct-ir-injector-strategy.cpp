//
// Created by Johny Georges on 2024-08-14.
//

#include "struct-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"

llvm::Value* StructIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_STRUCT_EXPRESSION_NODE)) {
        return this->inject((IRStructExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StructIRInjectorStrategy::inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto structExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())->inject(
                irExpressionAtIndex, builder, irInjectorMap, irOperationType, irModule);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return builder->get()->CreateLoad(structExpressionAllocation->getType(), structExpressionAllocation);
}

llvm::Value* StructIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irOperationType == IR_OPERAND_OP) {
        return irExpression->getSourceAllocation().value()->getParentAllocation().value()->getValue();
    }
    return StructIRInjectorHelper::injectStruct(
        builder,
        irExpression->getSourceAllocation().value()->getParentAllocation().value()
    )->getValue();
}

llvm::Value* StructIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto loadedSourceAllocation = StructIRInjectorHelper::extractNestedStructAllocation(irExpression);
    if (irOperationType == IR_OPERAND_OP) {
        return loadedSourceAllocation->getChildAllocationForKey(*irExpression->getTargetKey())->getValue();
    }
    return StructIRInjectorHelper::injectStruct(
            builder,
            loadedSourceAllocation->getChildAllocationForKey(*irExpression->getTargetKey())
    )->getValue();
}

llvm::Value* StructIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto loadedPointerToIndexedElement = ArrayIRInjectorHelper::extractNestedArrayAllocation(builder, irExpression, irInjectorMap, irModule);
    if (irOperationType == IR_OPERAND_OP) {
        return loadedPointerToIndexedElement;
    }
    throw std::logic_error("StructIRInjectorStrategy not implemented for IRArrayAccessExpressionNode + irOperationType");
}