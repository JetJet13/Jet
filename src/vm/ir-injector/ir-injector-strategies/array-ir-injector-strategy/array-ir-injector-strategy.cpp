//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-nodes/ir-module-node.h"

llvm::Value * ArrayIRInjectorStrategy::inject(IRExpressionNode *irExpression,
                                              std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap,
                                              IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_ARRAY_EXPRESSION_NODE)) {
        return this->inject((IRArrayExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    }
    throw std::logic_error("ArrayIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRArrayExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    builder->get()->Insert(irExpression->getSourceAggregateAllocation()->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getSourceAggregateAllocation()->getAllocatedType(),
                                                         irExpression->getSourceAggregateAllocation()->getValue(), {zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(elementExpression->getTypeSignature())->inject(
                elementExpression, builder, irInjectorMap, irOperationType, irModule);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder)->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto arrayAllocation = irExpression->getSourceAllocation().value()->getParentAllocation().value();
        builder->get()->Insert(arrayAllocation->getValue());
        auto type = irExpression->getSource()->getIRType()->getSourceType()->getType()->getStructElementType(irExpression->getTargetKeyIndex());
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getType(),
                irExpression->getSource()->getValue(),
                { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        builder->get()->Insert(pointer);
        auto loaded = builder->get()->CreateLoad(type, pointer);
        builder->get()->CreateStore(loaded, arrayAllocation->getValue());
        return ArrayIRInjectorHelper::injectArrayPointer(
                builder,
                irArrayPointerType,
                type->getArrayNumElements(),
                arrayAllocation,
                irExpression->getSourceAllocation().value())->getValue();
    } else if (irExpression->getSource()->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        auto arrayAccessAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        builder->get()->Insert(pointer);
        auto loadedPointerToIndexedElement = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return ArrayIRInjectorHelper::injectArrayCopy(builder, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
    }

    auto loadedSourceAllocation = StructIRInjectorHelper::extractNestedStructAllocation(irExpression);
    if (irOperationType == IR_OPERAND_OP) {
        return loadedSourceAllocation->getChildAllocationForKey(*irExpression->getTargetKey())->getValue();
    }
    return ArrayIRInjectorHelper::injectArrayPointer(
            builder,
            loadedSourceAllocation->getChildAllocationForKey(*irExpression->getTargetKey())
    )->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irOperationType == IR_OPERAND_OP) {
        return irExpression->getValue();
    }
    throw std::logic_error("cannot inject array from IRIdentifierExpressionNode. It must be IRAggregateIdentifierExpressionNode");
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    irInjectorMap->getInjector(irExpression->getSourceExpression()->getTypeSignature())->inject(irExpression->getSourceExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
    auto loadedPointerToIndexedElement = ArrayIRInjectorHelper::extractNestedArrayAllocation(builder, irExpression, irInjectorMap, irModule);
    if (irOperationType == IR_OPERAND_OP) {
        return loadedPointerToIndexedElement;
    }
    return ArrayIRInjectorHelper::injectArrayCopy(
            builder,
            (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType(),
            ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType(),
            irModule,
            loadedPointerToIndexedElement,
            irExpression->getSourceAllocation().value()
    )->getValue();
}
