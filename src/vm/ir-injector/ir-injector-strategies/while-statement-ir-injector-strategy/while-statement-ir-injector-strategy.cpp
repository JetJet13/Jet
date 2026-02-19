//
// Created by Johny Georges on 2025-05-24.
//

#include "while-statement-ir-injector-strategy.h"

void WhileStatementIRInjectorStrategy::inject(IRWhileStatementNode* irWhileStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto whileConditionBlock = irWhileStatement->getWhileBlock();
    auto bodyBlock = irWhileStatement->getBodyBlock();
    auto endBlock = irWhileStatement->getEndBlock();

    auto irWhileConditionValue = irInjector->inject(whileConditionBlock, irWhileStatement->getExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, whileConditionBlock->getScope());
    whileConditionBlock->getBuilder()->get()->CreateCondBr(irWhileConditionValue, bodyBlock->getBlock(), endBlock->getBlock());

    irInjector->inject(irBlock, bodyBlock, irModule);
    bodyBlock->getBuilder()->get()->CreateBr(whileConditionBlock->getBlock());
}