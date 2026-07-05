//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* StringIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->isOperandPointer()) {
        return pointer;
    } else if (irOperation->isOperandValue()) {
        auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getUnderlyingIRType());
        return InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), pointer, irBlock, arrayPointerType);
    }
    irBlock->getBuilder()->get()->Insert(irExpression->getSourceAllocation().value()->getValue());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStringFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    pointer,
            }
    );

    return InstructionIRInjectorHelper::injectLoad(irExpression->getSourceAllocation().value(), irBlock);
}