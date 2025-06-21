//
// Created by Johny Georges on 2025-06-21.
//

#include "ref-array-access-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-ref-array-access-type.h"

llvm::Value* RefArrayAccessIRInjectorHelper::inject(IRRefArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    auto irRefArrayAccessType = (IRRefArrayAccessType*)irExpression->getSourceAllocation().value()->getIRType()->getSourceType();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto accessIndex = irBlock->getBuilder()->get()->getInt32(irRefArrayAccessType->getAccessIndex());
    auto arrayIndex = irBlock->getBuilder()->get()->getInt32(irRefArrayAccessType->getArrayIndex());
    auto accessPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irRefArrayAccessType->getType(), allocation, { zeroIndex, accessIndex });
    irBlock->getBuilder()->get()->CreateStore(indexValue, accessPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irRefArrayAccessType->getType(), allocation, { zeroIndex, arrayIndex });
    irBlock->getBuilder()->get()->CreateStore(sourceValue, arrayPointer);
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return irBlock->getBuilder()->get()->CreateLoad(irRefArrayAccessType->getType(), allocation);
    }
    return allocation;
}