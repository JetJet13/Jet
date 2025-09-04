//
// Created by Johny Georges on 2025-06-21.
//

#include "dref-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-ref-type.h"

llvm::Value* DrefIRInjectorHelper::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getExpression()->getIRType()->getSourceType();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto refValueIndex = irBlock->getBuilder()->get()->getInt64(irRefType->getRefValueIndex());
    auto refValue = irInjector->inject(irBlock, irExpression->getExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto irValuePointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getExpression()->getIRType()->getSourceType()->getType(), refValue, { zeroIndex, refValueIndex });
    auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getExpression()->getIRType()->getType(), irValuePointer);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), loadedValue);
}