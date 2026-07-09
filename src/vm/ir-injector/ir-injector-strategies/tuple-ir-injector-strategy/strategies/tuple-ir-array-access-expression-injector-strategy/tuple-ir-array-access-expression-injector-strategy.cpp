//
// Created by Johny Georges on 2026-05-18.
//

#include "tuple-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* TupleIRArrayAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
    return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
}

llvm::Value* TupleIRArrayAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto arrayPointerIRType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getSourceExpression()->getUnderlyingIRType());
    auto elementIRType = arrayPointerIRType->getElementIRType();
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    auto typeValue = irInjector->inject(irBlock, elementIRType, irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(elementIRType->getValue()->getAllocatedType(), typeValue, irBlock);
    auto sourceAlloc = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStructRefFunction(),
            {
                    sourceAlloc,
                    pointerAtIndex,
                    loadedTypeValue
            }
    );
    return InstructionIRInjectorHelper::injectLoad(elementIRType->getType(), sourceAlloc, irBlock, elementIRType);
}

llvm::Value* TupleIRArrayAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto elementIRType = irExpression->getIRType();
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }
    return InstructionIRInjectorHelper::injectLoad(elementIRType->getType(), pointerAtIndex, irBlock, elementIRType);
}