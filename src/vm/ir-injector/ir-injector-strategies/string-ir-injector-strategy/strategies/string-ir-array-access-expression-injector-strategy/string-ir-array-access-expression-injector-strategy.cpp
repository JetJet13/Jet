//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getIRType());
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    auto sourceAlloc = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getCopyStringFunction(),
        {
            sourceAlloc,
            pointerAtIndex,
        }
    );
    return InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), sourceAlloc, irBlock, arrayPointerType);
}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getIRType());
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }
    return InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), pointerAtIndex, irBlock, arrayPointerType);
}