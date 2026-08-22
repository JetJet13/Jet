//
// Created by Johny Georges on 2025-01-09.
//

#include "if-statement-ir-injector-strategy.h"

void IfStatementIRInjectorStrategy::inject(std::shared_ptr<IRIfStatementNode> irIfStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irBlock->getLastChildOrSelf()->getBuilder()->get()->CreateBr(irIfStatement->getIfElseNode()->getIfBlock()->getBlock());
    auto endBlock = irIfStatement->getIfElseNode()->getEndBlock();
    std::optional<std::shared_ptr<IRIfElseNode>> currentIfElseNode = irIfStatement->getIfElseNode();
    while (currentIfElseNode) {
        auto ifConditionBlock = currentIfElseNode.value()->getIfBlock();
        auto thenBlock = currentIfElseNode.value()->getThenBlock();
        auto elseBlock = currentIfElseNode.value()->getElseBlock();

        auto irIfConditionValue = irInjector->inject(ifConditionBlock, currentIfElseNode.value()->getExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
        ifConditionBlock->getBuilder()->get()->CreateCondBr(irIfConditionValue, thenBlock->getBlock(), elseBlock->getBlock());
        irInjector->inject(irBlock, thenBlock, irModule);
        irInjector->inject(irBlock, elseBlock, irModule);

        elseBlock->getBlock()->moveAfter(thenBlock->getLastChildOrSelf()->getBlock());
        endBlock->getBlock()->moveAfter(elseBlock->getLastChildOrSelf()->getBlock());

        if (!thenBlock->getLastChildOrSelf()->hasBranchInstruction() && !thenBlock->getLastChildOrSelf()->hasReturnInstruction()) {
            thenBlock->getLastChildOrSelf()->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        if (currentIfElseNode.value()->getNext()) {
            elseBlock->getBuilder()->get()->CreateBr(currentIfElseNode.value()->getNext().value()->getIfBlock()->getBlock());
        } else if (irIfStatement->getElseNode()) {
            auto finalElseBlock = irIfStatement->getElseNode().value();
            elseBlock->getBuilder()->get()->CreateBr(finalElseBlock->getBlock());
            irInjector->inject(irBlock, finalElseBlock, irModule);
            if (!finalElseBlock->getLastChildOrSelf()->hasBranchInstruction() && !finalElseBlock->getLastChildOrSelf()->hasReturnInstruction()) {
                finalElseBlock->getLastChildOrSelf()->getBuilder()->get()->CreateBr(endBlock->getBlock());
            }
        } else {
            elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
        }

        currentIfElseNode = currentIfElseNode.value()->getNext();
    }

    auto parentBlock = irBlock->getParentBlock().value_or(irBlock);
    irIfStatement->getIfElseNode()->nestIn(parentBlock);
    if (irIfStatement->getElseNode()) {
        parentBlock->nest(irIfStatement->getElseNode().value());
    }

    if (!endBlock->hasReturnInstruction() && endBlock->isReachable()) {
        parentBlock->createChild();
        irIfStatement->getIfElseNode()->getEndBlock()->getBuilder()->get()->CreateBr(
                parentBlock->getLastChildOrSelf()->getBlock()
        );
        parentBlock->getLastChildOrSelf()->getBlock()->moveAfter(irIfStatement->getIfElseNode()->getEndBlock()->getBlock());
    } else if (endBlock->isUnreachable()) {
        irIfStatement->getIfElseNode()->getEndBlock()->addVoidReturn();
    }
}