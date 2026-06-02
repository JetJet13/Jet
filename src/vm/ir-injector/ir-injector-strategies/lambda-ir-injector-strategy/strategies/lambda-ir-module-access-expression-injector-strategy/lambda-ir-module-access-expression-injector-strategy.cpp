//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-module-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"

llvm::Value* LambdaIRModuleAccessExpressionInjectorStrategy::inject(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irExpression->getValue() });
    }

    return ModuleAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, irOperation);
}