//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-ref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRRefExpressionInjectorStrategy::inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto valueArc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        auto valueMalloc = this->setupRef(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
        if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
            return valueMalloc;
        } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
            return value;
        }
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        auto valueMalloc = this->setupRef(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
        if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
            return valueMalloc;
        } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
            return value;
        }
    } else {
        auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
        auto valueMalloc = this->setupRef(allocation, value, valueArc, irExpression->getUnderlyingIRType(), irBlock, irModule, irOperation);
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

llvm::Value* RefIRRefExpressionInjectorStrategy::setupRef(llvm::Value* allocation, llvm::Value* value, llvm::Value* valueArc, IRType* irType, IRBlockNode* irBlock, std::shared_ptr<IRModuleNode> irModule, IROperation* irOperation) {
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
                irModule->getSetupRefFunction(),
                { allocation, malloc, valueArc }
        );

    if (irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { allocation });
    }
    return malloc;
}

llvm::Value* RefIRRefExpressionInjectorStrategy::injectRawValue(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto rawValue = irInjector->inject(irBlock, irExpression->getExpression(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    if (irOperation->isRefGlobalAssignment()) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getIRType()->getSourceType()->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->get()->insertGlobalVariable(globalVariable);
        InstructionIRInjectorHelper::injectStore(rawValue, globalVariable, irBlock, irExpression->getIRType()->getRefValueIRType());
        return rawValue;
    }

    return rawValue;
}