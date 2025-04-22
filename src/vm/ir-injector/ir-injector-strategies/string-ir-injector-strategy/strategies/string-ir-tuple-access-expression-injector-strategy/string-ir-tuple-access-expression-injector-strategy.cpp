//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* StringIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                irExpression->getSourceAllocation().value()->getValue(),
                loadedPointerToIndexedElement,
                typeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}