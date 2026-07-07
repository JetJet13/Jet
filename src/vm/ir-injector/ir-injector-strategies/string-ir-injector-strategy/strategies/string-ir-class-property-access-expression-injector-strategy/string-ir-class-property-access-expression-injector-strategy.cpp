//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irArrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getIRType());
    auto pointerToPropertyValue = ClassPropertyAccessIRInjectorHelper::inject(
            irExpression,
            irBlock,
            irInjector,
            irModule,
            scope,
            (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying()
    );

    if (irOperation->isOperandPointer()) {
        return pointerToPropertyValue;
    } else if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getType(), pointerToPropertyValue, irBlock);
    }

    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStringFunction(),
            {
                destinationAllocation,
                pointerToPropertyValue
            }
    );
    return InstructionIRInjectorHelper::injectLoad(destinationAllocation->getAllocatedType(), destinationAllocation, irBlock);
}