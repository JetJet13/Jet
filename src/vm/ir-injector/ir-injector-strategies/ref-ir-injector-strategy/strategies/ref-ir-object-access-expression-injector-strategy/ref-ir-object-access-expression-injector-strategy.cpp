//
// Created by Johny Georges on 2025-09-20.
//

#include "ref-ir-object-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
     if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::injectCopy(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irStructRefType = (IRStructRefType*)irExpression->getIRType()->getSourceType();
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    auto loadedPointerToIndexedElement = InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
    return StructIRInjectorHelper::injectStructRefCopy(irBlock, irStructRefType, loadedPointerToIndexedElement,
                                                       irModule, irInjector);
}

llvm::Value* RefIRObjectAccessExpressionInjectorStrategy::injectOperand(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointerToIndexedElement = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, loadedPointerToIndexedElement);
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement, irBlock);
    }
    return pointerToIndexedElement;
}