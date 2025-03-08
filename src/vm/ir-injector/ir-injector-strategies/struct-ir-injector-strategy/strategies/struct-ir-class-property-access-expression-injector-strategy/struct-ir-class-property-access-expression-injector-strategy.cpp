//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* StructIRClassPropertyAccessExpressionInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
    auto loadedStruct = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
    irBlock->getBuilder()->get()->CreateStore(loadedStruct, allocation);
    return allocation;
}