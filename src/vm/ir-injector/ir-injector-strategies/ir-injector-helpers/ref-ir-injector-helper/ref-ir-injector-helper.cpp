//
// Created by Johny Georges on 2026-06-02.
//

#include "ref-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void RefIRInjectorHelper::incrementRefCountForInvocationExpression(llvm::Value* value, IRType* irType, IRBlockNode* irBlock, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule) {
    if (irOperation->isFunctionArgument()) {
        auto alloca = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, alloca, irBlock, irType);
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { alloca });
    }
}

llvm::Value* RefIRInjectorHelper::inject(llvm::Value* value, IRRefType* irRefType, IRBlockNode* irBlock, IROperation* irOperation) {
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), value, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), value, irRefType->getRefValueIndex());
        auto refValuePointer = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), refValuePointer, irBlock);
    } else if (irOperation->isOperandValue()) {

    }
    return value;
}