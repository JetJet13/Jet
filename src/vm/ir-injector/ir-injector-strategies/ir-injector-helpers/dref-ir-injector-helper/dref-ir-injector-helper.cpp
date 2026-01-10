//
// Created by Johny Georges on 2025-06-21.
//

#include "dref-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-ref-type.h"

llvm::Value* DrefIRInjectorHelper::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getExpression()->getIRType()->getSourceType();
    auto refValue = irInjector->inject(irBlock, irExpression->getExpression(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto irValuePointer = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), refValue, irRefType->getRefValueIndex());
    return irBlock->getBuilder()->get()->CreateLoad(irRefType->getRefValueType(), irValuePointer);
}