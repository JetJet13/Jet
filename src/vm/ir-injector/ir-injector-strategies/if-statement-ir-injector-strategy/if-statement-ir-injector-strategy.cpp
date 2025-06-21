//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"

void IfStatementIRInjectorStrategy::inject(IRIfStatementNode* irIfStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();
    std::optional<IRIfElseNode*> currentIfElseNode = irIfStatement->getIfElseNode();
    while (currentIfElseNode) {
        auto ifConditionBlock = currentIfElseNode.value()->getIfBlock();
        auto thenBlock = currentIfElseNode.value()->getThenBlock();
        auto elseBlock = currentIfElseNode.value()->getElseBlock();

        auto irIfConditionValue = irInjector->inject(ifConditionBlock, currentIfElseNode.value()->getExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
        ifConditionBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());

        irInjector->inject(irBlock, thenBlock, irModule, scope);
        irInjector->inject(irBlock, elseBlock, irModule, scope);

        if (!llvm::isa<llvm::BranchInst>(thenBlock->getBlock()->back())) {
            thenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        if (currentIfElseNode.value()->getNext()) {
            elseBlock->getBuilder()->get()->CreateBr(currentIfElseNode.value()->getNext().value()->getIfBlock()->getBlock());
        } else if (!llvm::isa<llvm::BranchInst>(elseBlock->getBlock()->back())) {
            elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        currentIfElseNode = currentIfElseNode.value()->getNext();
    }

}