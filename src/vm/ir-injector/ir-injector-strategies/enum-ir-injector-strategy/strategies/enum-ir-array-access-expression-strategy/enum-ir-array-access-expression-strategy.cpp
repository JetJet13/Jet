//
// Created by Johny Georges on 2026-01-31.
//

#include "enum-ir-array-access-expression-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* EnumIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    } else {
        return InstructionIRInjectorHelper::injectLoad(
                irExpression->getUnderlyingIRType()->getType(),
                pointerAtIndex,
                irBlock
        );
    }
}

llvm::Value* EnumIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
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