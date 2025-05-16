//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-sref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRSrefExpressionInjectorStrategy::inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerToRef = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetupSrefFunction()->getFunctionType(),
            irModule->getSetupSrefFunction(),
            { allocation, pointerToRef }
    );
    return allocation;
}