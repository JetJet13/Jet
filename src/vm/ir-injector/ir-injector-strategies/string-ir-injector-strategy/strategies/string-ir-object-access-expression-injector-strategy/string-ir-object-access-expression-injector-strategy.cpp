//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-object-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRObjectAccessExpressionInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto objectAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getUnderlyingIRType()->getType(), objectAccessAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
//    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->Insert(irExpression->getSourceAllocation().value()->getValue());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyArrayFunction(),
            {
                irExpression->getSourceAllocation().value()->getValue(),
                pointer,
                loadedTypeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}