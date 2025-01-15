//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"

void IfStatementIRInjectorStrategy::inject(IRIfStatementNode* irIfStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {

    auto ifConditionBlock = irIfStatement->getIfElseNode()->getIfBlock();
    auto thenBlock = irIfStatement->getIfElseNode()->getThenBlock();
    auto elseBlock = irIfStatement->getIfElseNode()->getElseBlock();
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();

//    irBlock->getBuilder()->get()->SetInsertPoint(irBlock->getBlock(), irBlock->getBlock()->begin());
//    irBlock->getBuilder()->get()->CreateBr(ifConditionBlock->getBlock());

    auto irIfConditionValue = irInjector->inject(ifConditionBlock, irIfStatement->getIfElseNode()->getExpression(), IR_OPERAND_OP, irModule, scope);
    ifConditionBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());

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