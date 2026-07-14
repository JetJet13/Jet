//
// Created by Johny Georges on 2026-06-27.
//

#include "shared-ptr-ir-module-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-shared-ptr-type.h"

llvm::Value* SharedPtrIRModuleAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* SharedPtrIRModuleAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType()->getSourceType());
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
    return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock);
}

llvm::Value* SharedPtrIRModuleAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType()->getSourceType());
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock);
        return irBlock->getBuilder()->get()->CreateExtractValue(refValue, irSharedPtrType->getSharedValueIndex(), "NNN");
    }

    if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock);
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(refValue, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), underlyingValuePointer, irBlock, irSharedPtrType->getSharedValueIRType());
    }

    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }

    return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), irExpression->getValue(), irBlock, irSharedPtrType);
}