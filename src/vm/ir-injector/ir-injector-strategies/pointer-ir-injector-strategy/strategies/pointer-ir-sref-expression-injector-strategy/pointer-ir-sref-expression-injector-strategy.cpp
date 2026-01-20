//
// Created by Johny Georges on 2025-03-29.
//

#include "pointer-ir-sref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRSrefExpressionInjectorStrategy::inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
    auto loadedPointerToValue = InstructionIRInjectorHelper::injectLoad(irExpression->getExpression()->getIRType()->getType(), pointerToPointerValue, irBlock);
//    auto loadedPointerToValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), pointerToPointerValue);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    InstructionIRInjectorHelper::injectStore(loadedPointerToValue, allocation, irBlock, irExpression->getIRType()->getRefValueIRType());
//    irBlock->getBuilder()->get()->CreateStore(loadedPointerToValue, allocation);
    return allocation;
}
