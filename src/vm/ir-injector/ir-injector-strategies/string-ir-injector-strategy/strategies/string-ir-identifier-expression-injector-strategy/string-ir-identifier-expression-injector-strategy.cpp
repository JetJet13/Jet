//
// Created by Johny Georges on 2025-04-26.
//

#include "string-ir-identifier-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRIdentifierExpressionInjectorStrategy::inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isCopy()|| irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        auto irArrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getUnderlyingIRType());
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationPointerAllocation, irExpression->getValue() });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), destinationPointerAllocation);
    }

    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), irExpression->getValue(), irBlock);
    }
    return irExpression->getValue();
}