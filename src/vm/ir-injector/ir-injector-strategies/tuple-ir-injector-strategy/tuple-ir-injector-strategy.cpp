//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* TupleIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->inject((IRTupleExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    }
    throw std::logic_error("TupleIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* TupleIRInjectorStrategy::inject(IRTupleExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto tupleExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(tupleExpressionAllocation->getType(), tupleExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())->inject(
                irExpressionAtIndex, builder, irInjectorMap, irOperationType, irModule);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return tupleExpressionAllocation;
}

llvm::Value* TupleIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irOperationType == IR_OPERAND_OP) {
        return irExpression->getValue();
    }
    return StructIRInjectorHelper::injectStructCopy(
        builder,
        (IRStructType*)irExpression->getIRType()->getSourceType(),
        irExpression->getValue(),
        irModule
    );
}

llvm::Value* TupleIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    Logger::log("TupleIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression", irOperationType);
    auto irStructType = (IRStructType*)irExpression->getIRType();
    if (irOperationType == IR_COPY_ASSIGNMENT_OP) {
        auto tupleAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), tupleAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        builder->get()->Insert(pointer);
        auto loadedPointerToIndexedElement = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return StructIRInjectorHelper::injectStructCopy(builder, irStructType, loadedPointerToIndexedElement, irModule);
    } else {
        auto loadedPointerToIndexedElement = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
        auto pointerToIndexedElement = builder->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
}