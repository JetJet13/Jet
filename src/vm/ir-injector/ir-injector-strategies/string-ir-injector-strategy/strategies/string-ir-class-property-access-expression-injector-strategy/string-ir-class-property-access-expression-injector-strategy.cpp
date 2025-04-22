//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"

llvm::Value* StringIRClassPropertyAccessExpressionInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto loadedPointerToIndexedElement = ClassPropertyAccessIRInjectorHelper::inject(irExpression,
                                                                                     irBlock,
                                                                                     irInjector,
                                                                                     irModule, scope);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    loadedPointerToIndexedElement,
                    typeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}