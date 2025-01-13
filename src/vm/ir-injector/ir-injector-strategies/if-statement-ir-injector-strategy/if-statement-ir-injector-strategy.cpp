//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"

void IfStatementIRInjectorStrategy::inject(IRIfStatementNode* irIfStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irIfConditionValue = irInjector->inject(irBlock, irIfStatement->getIfElseNode()->getExpression(), IR_OPERAND_OP, irModule, scope);

    auto thenBlock = irIfStatement->getIfElseNode()->getThenBlock();
    auto elseBlock = irIfStatement->getIfElseNode()->getElseBlock();
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();

    // todo: fix this. For some reason, it's not working
    irBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());

    auto irFunction = irBlock->getBuilder()->get()->GetInsertBlock()->getParent();
    irFunction->insert(irFunction->end(), thenBlock->getBlock());
    irFunction->insert(irFunction->end(), elseBlock->getBlock());
    irFunction->insert(irFunction->end(), endBlock->getBlock());

    for (auto statement : *thenBlock->getBody()) {
        irInjector->inject(thenBlock, statement, irModule, scope);
    }

    for (auto statement : *elseBlock->getBody()) {
        irInjector->inject(elseBlock, statement, irModule, scope);
    }

    thenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    endBlock->getBuilder()->get()->CreateRet(endBlock->getBuilder()->get()->getInt32(0));

}