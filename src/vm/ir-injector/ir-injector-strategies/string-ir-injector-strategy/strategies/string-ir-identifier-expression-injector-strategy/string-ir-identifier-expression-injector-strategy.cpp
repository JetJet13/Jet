//
// Created by Johny Georges on 2025-04-26.
//

#include "string-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"

llvm::Value* StringIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getUnderlyingIRType();
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationPointerAllocation, irExpression->getValue() });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), destinationPointerAllocation);
    }
    return irExpression->getValue();
}