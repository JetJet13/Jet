//
// Created by Johny Georges on 2025-05-10.
//

#include "shared-ptr-ir-share-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* SharedPtrIRShareExpressionInjectorStrategy::inject(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto valueArc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE, IR_ARRAY_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        auto valueMalloc = this->setupSharedPtr(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
        if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
            return valueMalloc;
        } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
            return value;
        }
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        auto valueMalloc = this->setupSharedPtr(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
        if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
            return valueMalloc;
        } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
            return value;
        }
    } else {
        auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
        auto valueMalloc = this->setupSharedPtr(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
        if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
            return valueMalloc;
        } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
            return value;
        }
    }

    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), allocation);
}

llvm::Value* SharedPtrIRShareExpressionInjectorStrategy::setupSharedPtr(llvm::Value* allocation, llvm::Value* value, llvm::Value* valueArc, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IROperation> irOperation) {
        auto sizeInBytes = irBlock->getBuilder()->get()->getInt64(irType->getSourceType()->getSizeInBytes());
        auto malloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                sizeInBytes
            }
        );
        InstructionIRInjectorHelper::injectStore(value, malloc, irBlock, irType->getSourceType());
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getSetupSharedPtrFunction(),
                { allocation, malloc, valueArc }
        );

    if (irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { allocation });
    }
    return malloc;
}

llvm::Value* SharedPtrIRShareExpressionInjectorStrategy::injectRawValue(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    return irInjector->inject(irBlock, irExpression->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
}