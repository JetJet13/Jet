//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"

void IfStatementIRInjectorStrategy::inject(IRIfStatementNode* irIfStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();
    std::optional<IRIfElseNode*> currentIfElseNode = irIfStatement->getIfElseNode();
    while (currentIfElseNode) {
        auto ifConditionBlock = currentIfElseNode.value()->getIfBlock();
        auto thenBlock = currentIfElseNode.value()->getThenBlock();
        auto elseBlock = currentIfElseNode.value()->getElseBlock();

        auto irIfConditionValue = irInjector->inject(ifConditionBlock, currentIfElseNode.value()->getExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
        ifConditionBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());
        irInjector->inject(irBlock, thenBlock, irModule);
        irInjector->inject(irBlock, elseBlock, irModule);

        elseBlock->getBlock()->moveAfter(thenBlock->getLastChildOrSelf()->getBlock());
        endBlock->getBlock()->moveAfter(elseBlock->getLastChildOrSelf()->getBlock());

        if (!thenBlock->hasBranchInstruction() && !thenBlock->hasReturnInstruction()) {
            thenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        if (currentIfElseNode.value()->getNext()) {
            elseBlock->getBuilder()->get()->CreateBr(currentIfElseNode.value()->getNext().value()->getIfBlock()->getBlock());
        } else if (irIfStatement->getElseNode()) {
            auto finalElseBlock = irIfStatement->getElseNode().value();
            elseBlock->getBuilder()->get()->CreateBr(finalElseBlock->getBlock());
            irInjector->inject(irBlock, finalElseBlock, irModule);
            if (!finalElseBlock->hasBranchInstruction() && !finalElseBlock->hasReturnInstruction()) {
                finalElseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
            }
        } else {
            elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        currentIfElseNode = currentIfElseNode.value()->getNext();
    }
}