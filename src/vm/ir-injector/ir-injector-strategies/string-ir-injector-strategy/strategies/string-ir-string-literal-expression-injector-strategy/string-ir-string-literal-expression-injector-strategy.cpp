//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-string-literal-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRStringLiteralExpressionInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    auto stringAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getValue()->getType());
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), stringAllocation);
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    auto zero = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < irExpression->getValue()->getType()->getArrayNumElements(); ++i) {
        auto index = irBlock->getBuilder()->get()->getInt32(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRType()->getElementType(), arrayAllocation, { index });
        auto pointerToChar = irBlock->getBuilder()->get()->CreateInBoundsGEP(stringAllocation->getAllocatedType(), stringAllocation, { zero, index });
        auto loadedChar = irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getElementType(), pointerToChar);
        irBlock->getBuilder()->get()->CreateStore(loadedChar, pointer);
    }
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    auto array = ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
    if (irOperationType == IR_OPERAND_POINTER_OP) {
        return irExpression->getAggregatePointerAllocation()->getValue();
    }
    return array;
}