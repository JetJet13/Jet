//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-sref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRSrefExpressionInjectorStrategy::inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToRef = irInjector->inject(irBlock, irExpression->getExpression(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetupSrefFunction()->getFunctionType(),
            irModule->getSetupSrefFunction(),
            { allocation, pointerToRef }
    );
    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRValue()->getAllocatedType(), allocation, irBlock);
//    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRValue()->getAllocatedType(), allocation);
}