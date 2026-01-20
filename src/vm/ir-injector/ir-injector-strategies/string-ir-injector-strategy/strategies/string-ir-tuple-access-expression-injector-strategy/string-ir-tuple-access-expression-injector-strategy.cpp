//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* StringIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->isOperandPointer()) {
        return pointer;
    }
    auto loadedPointerToIndexedElement = InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
    if (irOperation->isOperandValue()) {
        return loadedPointerToIndexedElement;
    }
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                irExpression->getSourceAllocation().value()->getValue(),
                loadedPointerToIndexedElement,
                loadedTypeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}