//
// Created by Johny Georges on 2026-05-19.
//

#include "class-instance-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ClassInstanceIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto irType = irExpression->getIRType();
    auto typeValue = irInjector->inject(irBlock, irType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getCopyStructRefFunction(),
        {
            allocation,
            pointerToValue,
            loadedTypeValue
        }
    );
    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irType->getType(), allocation, irBlock, irType);
}