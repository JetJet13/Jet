//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"

void IfStatementIRInjectorStrategy::inject(IRIfStatementNode* irIfStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto ifConditionBlock = irIfStatement->getIfElseNode()->getIfBlock();
    auto thenBlock = irIfStatement->getIfElseNode()->getThenBlock();
    auto elseBlock = irIfStatement->getIfElseNode()->getElseBlock();
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();

    auto irIfConditionValue = irInjector->inject(ifConditionBlock, irIfStatement->getIfElseNode()->getExpression(), IR_OPERAND_OP, irModule, scope);
    ifConditionBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());

    irInjector->inject(irBlock, thenBlock, irModule, scope);
    irInjector->inject(irBlock, elseBlock, irModule, scope);

    if (!llvm::isa<llvm::BranchInst>(thenBlock->getBlock()->back())) {
        thenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    }

    if (!llvm::isa<llvm::BranchInst>(elseBlock->getBlock()->back())) {
        elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    }

}