//
// Created by Johny Georges on 2025-03-19.
//

#include "struct-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"

llvm::Value* StructIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irPointerValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), irPointerValue);
    auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), loadedPointer);
    return StructIRInjectorHelper::injectStructCopy(
            irBlock,
            (IRStructType*)irExpression->getIRType(),
            loadedValue,
            irModule,
            irOperationType
    );
}