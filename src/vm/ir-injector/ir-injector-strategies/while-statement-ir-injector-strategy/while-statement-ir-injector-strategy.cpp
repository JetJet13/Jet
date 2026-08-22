//
// Created by Johny Georges on 2025-05-24.
//

#include "while-statement-ir-injector-strategy.h"

void WhileStatementIRInjectorStrategy::inject(std::shared_ptr<IRWhileStatementNode> irWhileStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irBlock->getLastChildOrSelf()->getBuilder()->get()->CreateBr(irWhileStatement->getWhileBlock()->getBlock());

    auto whileConditionBlock = irWhileStatement->getWhileBlock();
    auto bodyBlock = irWhileStatement->getBodyBlock();
    auto endBlock = irWhileStatement->getEndBlock();

    auto irWhileConditionValue = irInjector->inject(whileConditionBlock, irWhileStatement->getExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, whileConditionBlock->getScope());
    whileConditionBlock->getBuilder()->get()->CreateCondBr(irWhileConditionValue, bodyBlock->getBlock(), endBlock->getBlock());

    irInjector->inject(irBlock, bodyBlock, irModule);
    auto lastBodyBlock = bodyBlock->getLastChildOrSelf();
    if (lastBodyBlock->hasBranchInstruction()) {
        lastBodyBlock->removeLastInstruction();
    }
    lastBodyBlock->getBuilder()->get()->CreateBr(whileConditionBlock->getBlock());

    auto parentBlock = irBlock->getParentBlock().value_or(irBlock);
    irWhileStatement->nestIn(parentBlock);
    parentBlock->createChild();
    irWhileStatement->getEndBlock()->getBuilder()->get()->CreateBr(
        parentBlock->getLastChildOrSelf()->getBlock()
    );
    parentBlock->getLastChildOrSelf()->getBlock()->moveAfter(irWhileStatement->getEndBlock()->getBlock());
}