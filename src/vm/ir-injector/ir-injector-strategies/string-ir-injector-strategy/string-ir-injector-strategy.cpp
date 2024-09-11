//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* StringIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType);
    }
    throw std::logic_error("StringIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    builder->get()->Insert(arrayAllocation);
    builder->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder)->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType) {
//    builder->get()->Insert(irExpression->getSourceAllocation().value()->getValue());
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    return builder->get()->CreateAlloca(arrayPointerType->getType());

    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getIRType()->getSourceType()->getType(),
                irExpression->getSource()->getValue(),
                {builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex()}
        );
        builder->get()->Insert(pointer);
        auto loadedValue = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
//        builder->get()->CreateStore(loadedValue, irExpression->getSourceAllocation().value()->getValue());
//        auto arrayPointerTypeAllocation = builder->get()->CreateAlloca(arrayPointerType->getType());
//        return ArrayIRInjectorHelper::injectArrayPointer(
//                builder,
//                arrayPointerType,
//                irExpression->getSource()->,
//                arrayPointerTypeAllocation
//        );
    }

//    auto sourceAllocation = irExpression->getSource()->getRootAllocationAtIndex(irExpression->getTargetKeyIndex()).value();
//    ArrayIRInjectorHelper::injectArrayCopy(
//            builder,
//            sourceAllocation,
//            irExpression->getSourceAllocation().value());
//    auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(sourceAllocation, irExpression->getRootAllocation().value());
//    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, arrayPointerTypeAllocation);
}