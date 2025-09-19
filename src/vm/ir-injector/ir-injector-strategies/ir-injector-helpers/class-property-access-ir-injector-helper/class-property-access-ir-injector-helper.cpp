//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
//    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getSource()->getAllocatedType(), irExpression->getValue());
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(irExpression->getSource()->getAllocatedType(), irExpression->getValue(), irBlock);
    auto pointerToProperty = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getSourceType()->getType(), loadedPointer, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointerToProperty);
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointerToProperty, irBlock);
//    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointerToProperty);
}