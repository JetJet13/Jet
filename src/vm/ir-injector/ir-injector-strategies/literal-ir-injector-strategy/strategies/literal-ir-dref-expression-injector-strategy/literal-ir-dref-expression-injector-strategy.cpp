//
// Created by Johny Georges on 2025-03-19.
//

#include "literal-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"

llvm::Value* LiteralIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    InstructionIRInjectorHelper::injectStore(loadedValue, allocation, irBlock, irExpression->getIRType());
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRValue()->getAllocatedType(), allocation, irBlock);
}