//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->getIRType()->getSourceType()->getSourceType()->isArrayPointerType() &&
            (irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP)) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType()->getSourceType();
        auto loadedUnderlyingPointer = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), irExpression->getValue(), irBlock);
//        auto loadedUnderlyingPointer = irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), irExpression->getValue());
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
//        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationPointerAllocation, loadedUnderlyingPointer, loadedTypeValue });
        auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
        InstructionIRInjectorHelper::injectStore(destinationPointerAllocation, newPointer, irBlock, irArrayPointerType);
//        irBlock->getBuilder()->get()->CreateStore(destinationPointerAllocation, newPointer);
        return newPointer;
    }
    return irExpression->getValue();
}