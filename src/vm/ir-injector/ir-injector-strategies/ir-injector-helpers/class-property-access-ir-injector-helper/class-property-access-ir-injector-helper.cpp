//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-access-ir-injector-helper.h"

llvm::Value* ClassPropertyAccessIRInjectorHelper::inject(IRClassPropertyAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointer = builder->get()->CreateLoad(irExpression->getSource()->getIRType()->getSourceType()->getSourceType()->getType(), irExpression->getValue());
    auto pointerAllocation = builder->get()->CreateAlloca(loadedPointer->getType(), loadedPointer);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(pointerAllocation->getAllocatedType(), irExpression->getValue(), { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    builder->get()->Insert(pointer);
    return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
}