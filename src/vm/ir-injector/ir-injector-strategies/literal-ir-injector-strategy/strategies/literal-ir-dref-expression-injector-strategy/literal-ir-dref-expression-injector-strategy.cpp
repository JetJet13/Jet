//
// Created by Johny Georges on 2025-03-19.
//

#include "literal-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"

llvm::Value* LiteralIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    InstructionIRInjectorHelper::injectStore(loadedValue, allocation, irBlock, irExpression->getIRType());
//    irBlock->getBuilder()->get()->CreateStore(loadedValue, allocation);
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRValue()->getAllocatedType(), allocation, irBlock);
//    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRValue()->getAllocatedType(), allocation);
}