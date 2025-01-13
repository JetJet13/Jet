//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-access-ir-injector-helper.h"

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getSource()->getIRType()->getSourceType()->getSourceType()->getType(), irExpression->getValue());
    auto pointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(loadedPointer->getType(), loadedPointer);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(pointerAllocation->getAllocatedType(), irExpression->getValue(), { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
}