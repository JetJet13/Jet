//
// Created by Johny Georges on 2025-03-24.
//

#include "string-ir-dref-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"

llvm::Value* StringIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { irExpression->getIRValue()->getValue(), loadedValue });
    return irExpression->getIRValue()->getValue();
}