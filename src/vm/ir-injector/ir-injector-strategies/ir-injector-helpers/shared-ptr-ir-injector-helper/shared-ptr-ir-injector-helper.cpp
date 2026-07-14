//
// Created by Johny Georges on 2026-07-13.
//

#include "shared-ptr-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void SharedPtrIRInjectorHelper::incrementSharedPtrCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule) {
    if (irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { value });
    }
}

llvm::Value* SharedPtrIRInjectorHelper::injectForInvocationExpression(llvm::Value* value, std::shared_ptr<IRSharedPtrType> irSharedPtrType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation) {
    // value is expected to be a ptr
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), value, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), value, irSharedPtrType->getSharedValueIndex());
        auto refValuePointer = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), refValuePointer, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return value;
    }
    return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), value, irBlock);
}