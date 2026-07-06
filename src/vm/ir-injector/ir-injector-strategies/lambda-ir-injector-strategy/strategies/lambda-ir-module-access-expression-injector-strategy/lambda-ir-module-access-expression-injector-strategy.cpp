//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-module-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LambdaIRModuleAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irExpression->getValue() });
    }

    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}