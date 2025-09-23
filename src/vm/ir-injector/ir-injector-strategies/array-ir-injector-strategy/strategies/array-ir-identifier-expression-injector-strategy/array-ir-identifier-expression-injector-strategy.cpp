//
// Created by Johny Georges on 2025-04-25.
//

#include "array-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"

llvm::Value* ArrayIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRValue()->getIRType()->getUnderlyingType();
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationPointerAllocation, irExpression->getValue(), loadedTypeValue });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), destinationPointerAllocation);
    }
    return irExpression->getValue();
}