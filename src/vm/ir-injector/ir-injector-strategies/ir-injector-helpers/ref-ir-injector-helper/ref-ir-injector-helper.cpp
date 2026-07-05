//
// Created by Johny Georges on 2026-06-02.
//

#include "ref-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void RefIRInjectorHelper::incrementRefCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, IRBlockNode* irBlock, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule) {
    if (irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { value });
    }
}

llvm::Value* RefIRInjectorHelper::injectForInvocationExpression(llvm::Value* value, std::shared_ptr<IRRefType> irRefType, IRBlockNode* irBlock, IROperation* irOperation) {
    // value is expected to be a ptr
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), value, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), value, irRefType->getRefValueIndex());
        auto refValuePointer = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), refValuePointer, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return value;
    }
    return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), value, irBlock);
}