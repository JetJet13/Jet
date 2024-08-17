//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

llvm::Value* StringIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap);
    }
    throw std::logic_error("StringIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    auto arrayAllocation = irExpression->getSourceArrayAllocation()->getValue();
    builder->get()->Insert(arrayAllocation);
    builder->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(), irExpression->getSourceArrayAllocation(), irExpression->getArrayPointerAllocation());
}

llvm::Value* StringIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder);
}

llvm::Value* StringIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
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