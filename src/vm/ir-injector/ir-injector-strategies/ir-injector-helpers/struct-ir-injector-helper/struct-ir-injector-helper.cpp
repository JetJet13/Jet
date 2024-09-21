//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-global-identifier-expression-node.h"

IRLoadInstructionNode* StructIRInjectorHelper::injectStruct(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* structAllocation) {
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
        } else if (irTypeAtIndex->isStructType()) {
            auto nestedStructAllocation = structAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStruct(builder, nestedStructAllocation);
            builder->get()->CreateStore(loadedNestedStruct->getValue(), destinationPointer);
        } else {
                auto elementPointer = builder->get()->CreateInBoundsGEP(irStructType->getType(), structAllocation->getValue(), { zeroIndex, index });
                auto loadedValue = builder->get()->CreateLoad(irTypeAtIndex->getType(), elementPointer);
                builder->get()->CreateStore(loadedValue, destinationPointer);
            }
    }
    return new IRLoadInstructionNode(builder->get()->CreateLoad(destinationAllocation->getAllocatedType(), destinationAllocation->getValue()), destinationAllocation);
}

IRLoadInstructionNode* StructIRInjectorHelper::extractNestedStruct(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRObjectAccessExpressionNode* irExpression) {
    if (irExpression->getSource()->getIRType()->getSourceType()->isEnumType()) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
            irExpression->getSource()->getType(),
            irExpression->getSource()->getValue(),
            { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        builder->get()->Insert(pointer);
        auto loadedValue = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return new IRLoadInstructionNode(loadedValue, irExpression->getSource()->getSourceAllocation().value());
    }
    auto targetKeys = std::vector<std::string>();
    auto targetIndices = std::vector<llvm::Value*>();
    auto expression = irExpression->getSource();
    auto irStructType = (IRStructType*)irExpression->getSource()->getSourceAllocation().value()->getIRType()->getSourceType();
    targetIndices.insert(
            targetIndices.begin(),
            builder->get()->getInt32(irStructType->getIndexForKey(*irExpression->getTargetKey()))
    );
    while (expression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        auto objectAccessExpression = (IRObjectAccessExpressionNode*)expression;
        irStructType = (IRStructType*)objectAccessExpression->getSource()->getSourceAllocation().value()->getIRType()->getSourceType();
        targetKeys.insert(targetKeys.begin(), *objectAccessExpression->getTargetKey());
        targetIndices.insert(
                targetIndices.begin(),
                builder->get()->getInt32(irStructType->getIndexForKey(*objectAccessExpression->getTargetKey()))
        );
        expression = objectAccessExpression->getSource();
    }
    auto rootAllocation = expression->getSourceAllocation().value()->getParentAllocation().value();
    auto loadedAllocation = rootAllocation;
    for (auto targetKey : targetKeys) {
        loadedAllocation = loadedAllocation->getChildAllocationForKey(targetKey);
    }

    targetIndices.insert(targetIndices.begin(), builder->get()->getInt32(0));
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(rootAllocation->getAllocatedType(), rootAllocation->getValue(), targetIndices);
    builder->get()->Insert(pointer);
    auto loadedValue = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return new IRLoadInstructionNode(loadedValue, loadedAllocation);
}

IRInstructionNode* StructIRInjectorHelper::extractNestedStructAllocation(IRObjectAccessExpressionNode* irExpression) {
    auto targetKeys = std::vector<std::string>();
    auto expression = irExpression->getSource();
    while (expression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        auto objectAccessExpression = (IRObjectAccessExpressionNode*)expression;
        targetKeys.insert(targetKeys.begin(), *objectAccessExpression->getTargetKey());
        expression = objectAccessExpression->getSource();
    }
    auto rootAllocation = expression->getSourceAllocation().value()->getParentAllocation().value();
    auto loadedAllocation = rootAllocation;
    for (auto targetKey : targetKeys) {
        loadedAllocation = loadedAllocation->getChildAllocationForKey(targetKey);
    }
    return loadedAllocation;
}