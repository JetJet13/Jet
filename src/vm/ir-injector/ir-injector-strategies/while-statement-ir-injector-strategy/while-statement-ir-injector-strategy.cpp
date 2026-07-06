//
// Created by Johny Georges on 2025-05-24.
//

#include "while-statement-ir-injector-strategy.h"

void WhileStatementIRInjectorStrategy::inject(std::shared_ptr<IRWhileStatementNode> irWhileStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto whileConditionBlock = irWhileStatement->getWhileBlock();
    auto bodyBlock = irWhileStatement->getBodyBlock();
    auto endBlock = irWhileStatement->getEndBlock();

    auto irWhileConditionValue = irInjector->inject(whileConditionBlock, irWhileStatement->getExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, whileConditionBlock->getScope());
    whileConditionBlock->getBuilder()->get()->CreateCondBr(irWhileConditionValue, bodyBlock->getBlock(), endBlock->getBlock());

    irInjector->inject(irBlock, bodyBlock, irModule);
    auto lastBodyBlock = bodyBlock->getLastChildOrSelf();
    if (lastBodyBlock->hasBranchInstruction()) {
        lastBodyBlock->removeLastInstruction();
    }
    lastBodyBlock->getBuilder()->get()->CreateBr(whileConditionBlock->getBlock());
}