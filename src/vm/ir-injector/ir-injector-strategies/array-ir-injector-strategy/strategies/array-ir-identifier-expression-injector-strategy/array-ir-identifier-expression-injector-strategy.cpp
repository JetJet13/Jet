//
// Created by Johny Georges on 2025-04-25.
//

#include "array-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRValue()->getIRType()->getSourceType();
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(irArrayPointerType->getNumElementsIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(irArrayPointerType->getType(), irExpression->getValue(), { zeroIndex, numElementsIndex });
        auto numElements = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getNumElementsType(), pointerToNumElements);
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, irArrayPointerType, numElements, irModule);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationAllocation->getValue(), irExpression->getValue(), irArrayPointerType->getValue()->getValue() });
        return destinationAllocation->getValue();
    }
    return irExpression->getValue();
}