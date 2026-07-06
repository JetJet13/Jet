//
// Created by Johny Georges on 2026-06-15.
//

#include "class-instance-ir-this-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-struct-ref-type.h"

llvm::Value* ClassInstanceIRThisExpressionInjectorStrategy::inject(std::shared_ptr<IRThisExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* ClassInstanceIRThisExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRThisExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irType = std::dynamic_pointer_cast<IRStructRefType>(irExpression->getUnderlyingIRType());
    auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irType->getType());
    auto typeValue = irInjector->inject(irBlock, irType, irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
    auto pointerToValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), irExpression->getValue(), irBlock, irExpression->getUnderlyingIRType());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStructRefFunction(),
            {
                destinationPointerAllocation,
                pointerToValue,
                loadedTypeValue
            }
    );
    return InstructionIRInjectorHelper::injectLoad(irType->getType(), destinationPointerAllocation, irBlock);
}

llvm::Value* ClassInstanceIRThisExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRThisExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), irExpression->getValue(), irBlock, irExpression->getUnderlyingIRType());
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), pointerToValue, irBlock, irExpression->getUnderlyingIRType());
    }
    return pointerToValue;
}