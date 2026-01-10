//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isCopyReassignment() || irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), pointerAtIndex, irBlock);
}

llvm::Value* StructIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    auto pointerToArrayAlloc = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt64(0), allocIndex });
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), pointerToArrayAlloc, irBlock, arrayPointerType);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    return pointerToIndexedElement;
}