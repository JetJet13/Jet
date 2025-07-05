//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRClassPropertyAccessExpressionInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto loadedPointerToIndexedElement = ClassPropertyAccessIRInjectorHelper::inject(irExpression,
                                                                                     irBlock,
                                                                                     irInjector,
                                                                                     irModule, scope);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    auto destinationAllocation = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                    destinationAllocation,
                    loadedPointerToIndexedElement,
                    loadedTypeValue
            }
    );
    return irBlock->getBuilder()->get()->CreateLoad(
            irExpression->getSourceAllocation().value()->getAllocatedType(),
            destinationAllocation
    );
}