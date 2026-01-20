//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->getUnderlyingIRType()->isArrayPointerType() &&
            (irOperation->isCopy() || irOperation->isCopyGlobal())) {
        auto irArrayPointerType = (IRArrayPointerType*)irExpression->getUnderlyingIRType();
        auto loadedUnderlyingPointer = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), irExpression->getValue(), irBlock);
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationPointerAllocation, loadedUnderlyingPointer, loadedTypeValue });
        auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
        InstructionIRInjectorHelper::injectStore(destinationPointerAllocation, newPointer, irBlock, irArrayPointerType);
        return newPointer;
    }
    return irExpression->getValue();
}