//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

llvm::Value* StringIRInjector::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder);
    }
    throw std::logic_error("StringIRInjector - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjector::inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayAllocation = irExpression->getSourceArrayAllocation()->getValue();
    builder->get()->Insert(arrayAllocation);
    builder->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), irExpression->getArrayPointerAllocation());
}

llvm::Value* StringIRInjector::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder);
}

llvm::Value* StringIRInjector::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->Insert(irExpression->getSourceAllocation().value()->getValue());
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType();

    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getIRType()->getSourceType()->getType(),
                irExpression->getSource()->getValue(),
                {builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex()}
        );
        builder->get()->Insert(pointer);
        auto loadedValue = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        builder->get()->CreateStore(loadedValue, irExpression->getSourceAllocation().value()->getValue());
        auto arrayPointerTypeAllocation = builder->get()->CreateAlloca(arrayPointerType->getType());
        return ArrayIRInjectorHelper::injectArrayPointer(
                builder,
                arrayPointerType,
                irExpression->getSourceAllocation().value(),
                arrayPointerTypeAllocation
        );
    }

    auto sourceAllocation = irExpression->getSource()->getRootAllocationAtIndex(irExpression->getTargetKeyIndex()).value();
    ArrayIRInjectorHelper::injectArrayCopy(
            builder,
            sourceAllocation,
            irExpression->getSourceAllocation().value());
    auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(sourceAllocation, irExpression->getRootAllocation().value());
    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, arrayPointerTypeAllocation);
}