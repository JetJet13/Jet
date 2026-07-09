//
// Created by Johny Georges on 2026-05-20.
//

#include "enum-ir-dref-expression-strategy.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* EnumIRDrefExpressionInjectorStrategy::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irType = irExpression->getIRType();
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    if (irType->isArrayPointerType()) {
        auto pointerToValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyStringFunction(),
                {
                    allocation,
                    pointerToValue
                }
        );
    } else {
        auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
        InstructionIRInjectorHelper::injectStore(loadedValue, allocation, irBlock, irExpression->getIRType());
    }

    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRValue()->getAllocatedType(), allocation, irBlock);
}