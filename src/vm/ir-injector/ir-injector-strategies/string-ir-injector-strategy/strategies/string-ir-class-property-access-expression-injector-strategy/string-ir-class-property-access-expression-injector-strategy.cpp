//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRClassPropertyAccessExpressionInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto pointerToPropertyValue = ClassPropertyAccessIRInjectorHelper::inject(
            irExpression,
            irBlock,
            irInjector,
            irModule,
            scope,
            (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying()
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