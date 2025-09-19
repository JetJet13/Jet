//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    if (irOperationType == IR_COPY_REASSIGNMENT_OP || irOperationType == IR_OPERAND_POINTER_OP) {
        return pointerAtIndex;
    } else {
        return InstructionIRInjectorHelper::injectLoad(
                irExpression->getIRType()->getSourceType()->getType(),
                pointerAtIndex,
                irBlock
        );
//        return irBlock->getBuilder()->get()->CreateLoad(
//                irExpression->getIRType()->getSourceType()->getType(),
//                pointerAtIndex
//        );
    }
}

llvm::Value* LiteralIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(
            arrayPointerType->getType(),
            sourceValue,
            { zeroIndex, allocIndex }
    );
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), arrayAllocPointer, irBlock, arrayPointerType);
//    auto arrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), arrayAllocPointer);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });

}