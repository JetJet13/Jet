//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-logical-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRLogicalExpressionInjectorStrategy::inject(std::shared_ptr<IRLogicalExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto result = irBlock->getBuilder()->get()->CreateBinOp(
        irExpression->getValue()->getOpcode(),
        irExpression->getLeftNode()->getUnderlyingIRType()->isBoolType()
        ? irLeftNodeValue
        : irBlock->getBuilder()->get()->getTrue(),
        irExpression->getRightNode()->getUnderlyingIRType()->isBoolType()
        ? irRightNodeValue
        : irBlock->getBuilder()->get()->getTrue()
    );
    if (irOperation->isOperandPointer()) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(result->getType());
        InstructionIRInjectorHelper::injectStore(result, allocation, irBlock);
        return allocation;
    }
    return result;
}