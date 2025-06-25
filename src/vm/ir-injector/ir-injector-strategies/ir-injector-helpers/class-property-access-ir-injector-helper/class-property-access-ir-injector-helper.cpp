//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-access-ir-injector-helper.h"

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getSource()->getAllocatedType(), irExpression->getValue());
    auto pointerToProperty = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getSourceType()->getType(), loadedPointer, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointerToProperty);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointerToProperty);
}