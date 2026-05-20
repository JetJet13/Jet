//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto arrayPointerIRType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto elementIRType = arrayPointerIRType->getElementIRType();
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    auto typeValue = irInjector->inject(irBlock, elementIRType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(elementIRType->getValue()->getAllocatedType(), typeValue, irBlock);
    auto sourceAlloc = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getCopyArrayFunction(),
        {
            sourceAlloc,
            pointerAtIndex,
            loadedTypeValue
        }
    );
    return InstructionIRInjectorHelper::injectLoad(elementIRType->getType(), sourceAlloc, irBlock, elementIRType);
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto elementIRType = irExpression->getIRType();
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }
    return InstructionIRInjectorHelper::injectLoad(elementIRType->getType(), pointerAtIndex, irBlock, elementIRType);
}