//
// Created by Johny Georges on 2025-09-20.
//

#include "ref-ir-object-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
     if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointer });
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
}

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToIndexedElement = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, loadedPointerToIndexedElement);
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), pointerToIndexedElement, irBlock);
        return irBlock->getBuilder()->get()->CreateExtractValue(refValue, irRefType->getRefValueIndex());
    } else if (irOperation->isOperandPointer()) {
        return pointerToIndexedElement;
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), pointerToIndexedElement, irBlock);
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(refValue, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), underlyingValuePointer, irBlock, irRefType->getRefValueIRType());
    }
    return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), pointerToIndexedElement, irBlock);
}