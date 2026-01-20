//
// Created by Johny Georges on 2026-01-10.
//

#include "ref-ir-array-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"

llvm::Value* RefIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType();
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), pointerAtIndex, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    }
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointerAtIndex });
    return InstructionIRInjectorHelper::injectLoad(
            irRefType->getType(),
            pointerAtIndex,
            irBlock
    );
}

llvm::Value* RefIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateStructGEP(
            arrayPointerType->getType(),
            sourceValue,
            arrayPointerType->getAllocIndex()
    );
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), arrayAllocPointer, irBlock, arrayPointerType);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
}