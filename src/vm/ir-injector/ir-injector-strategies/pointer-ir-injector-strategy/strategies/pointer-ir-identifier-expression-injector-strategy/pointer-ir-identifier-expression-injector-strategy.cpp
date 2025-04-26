//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* PointerIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->getIRType()->getSourceType()->getSourceType()->isArrayPointerType() &&
            (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP)) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType()->getSourceType();
        auto loadedUnderlyingPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), irExpression->getValue());
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(irArrayPointerType->getNumElementsIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(irArrayPointerType->getType(), loadedUnderlyingPointer, { zeroIndex, numElementsIndex });
        auto numElements = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getNumElementsType(), pointerToNumElements);
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, irArrayPointerType, numElements, irModule);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationAllocation->getValue(), loadedUnderlyingPointer, irArrayPointerType->getValue()->getValue() });
        auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
        irBlock->getBuilder()->get()->CreateStore(destinationAllocation->getValue(), newPointer);
        return newPointer;
    }
    return irExpression->getValue();
}