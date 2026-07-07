//
// Created by Johny Georges on 2025-03-19.
//

#include "literal-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"

llvm::Value* LiteralIRDrefExpressionInjectorStrategy::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    InstructionIRInjectorHelper::injectStore(loadedValue, allocation, irBlock, irExpression->getIRType());
    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRValue()->getAllocatedType(), allocation, irBlock);
}