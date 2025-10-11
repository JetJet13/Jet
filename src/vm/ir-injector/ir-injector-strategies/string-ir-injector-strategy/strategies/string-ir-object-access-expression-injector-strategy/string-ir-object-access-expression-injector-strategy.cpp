//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-object-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRObjectAccessExpressionInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto objectAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getUnderlyingIRType()->getType(), objectAccessAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    if (irExpression->getSource()->getTypeSignature()->typeSourceIs(ENUM_TYPE_SOURCE)) {
        if (irOperation->isOperandPointer()) {
            return pointer;
        }
        return InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getType(), pointer, irBlock, irArrayPointerType);
    }
    irBlock->getBuilder()->get()->Insert(irExpression->getSourceAllocation().value()->getValue());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStringFunction(),
            {
                irExpression->getSourceAllocation().value()->getValue(),
                pointer,
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}