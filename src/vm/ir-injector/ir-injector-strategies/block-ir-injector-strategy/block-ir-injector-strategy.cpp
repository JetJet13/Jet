//
// Created by Johny Georges on 2025-05-19.
//

#include "block-ir-injector-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"

void BlockIRInjectorStrategy::inject(IRBlockNode* irBlockNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    auto successorsToBranchToParent = std::vector<IRBlockNode*>();
    for (auto statement : *irBlockNode->getBody()) {
        if (statement->is(IR_IF_STATEMENT_NODE)) {
            auto ifStatement = (IRIfStatementNode*)statement;
            irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(ifStatement->getIfElseNode()->getIfBlock()->getBlock());
            ifStatement->getIfElseNode()->setBlocksToBeSuccessorsOf(irBlockNode);
            if (ifStatement->getElseNode()) {
                irBlockNode->addSuccessor(ifStatement->getElseNode().value());
            }
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, irBlockNode->getLastSuccessorOrSelf()->getScope());
            if (!ifStatement->getIfElseNode()->getEndBlock()->hasReturnInstruction() && ifStatement->getIfElseNode()->getEndBlock()->isReachable()) {
                irBlockNode->createSuccessor();
                successorsToBranchToParent.push_back(irBlockNode->getLastSuccessorOrSelf());
                ifStatement->getIfElseNode()->getEndBlock()->getBuilder()->get()->CreateBr(
                        irBlockNode->getLastSuccessorOrSelf()->getBlock()
                );
                irBlockNode->getLastSuccessorOrSelf()->getBlock()->moveAfter(ifStatement->getIfElseNode()->getEndBlock()->getBlock());
            } else if (ifStatement->getIfElseNode()->getEndBlock()->isUnreachable()) {
                ifStatement->getIfElseNode()->getEndBlock()->addVoidReturn();
            }
        } else if (statement->is(IR_WHILE_STATEMENT_NODE)) {
            auto whileStatement = (IRWhileStatementNode*)statement;
            irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(whileStatement->getWhileBlock()->getBlock());
            whileStatement->setBlocksToBeSuccessorsOf(irBlockNode);
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, irBlockNode->getLastSuccessorOrSelf()->getScope());
            irBlockNode->createSuccessor();
            successorsToBranchToParent.push_back(irBlockNode->getLastSuccessorOrSelf());
            whileStatement->getEndBlock()->getBuilder()->get()->CreateBr(
                    irBlockNode->getLastSuccessorOrSelf()->getBlock()
            );
            irBlockNode->getLastSuccessorOrSelf()->getBlock()->moveAfter(whileStatement->getEndBlock()->getBlock());
        } else if (statement->is(IR_FOR_IN_STATEMENT_NODE)) {
            auto forInStatement = (IRForInStatementNode*)statement;
            irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(forInStatement->getSetupBlock()->getBlock());
            forInStatement->setBlocksToBeSuccessorsOf(irBlockNode);
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, irBlockNode->getLastSuccessorOrSelf()->getScope());
            irBlockNode->createSuccessor();
            successorsToBranchToParent.push_back(irBlockNode->getLastSuccessorOrSelf());
            forInStatement->getEndBlock()->getBuilder()->get()->CreateBr(
                    irBlockNode->getLastSuccessorOrSelf()->getBlock()
            );
            irBlockNode->getLastSuccessorOrSelf()->getBlock()->moveAfter(forInStatement->getEndBlock()->getBlock());
        } else if (!irBlockNode->getLastSuccessorOrSelf()->hasReturnInstruction() && !irBlockNode->getLastSuccessorOrSelf()->hasBranchInstruction()) {
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, irBlockNode->getLastSuccessorOrSelf()->getScope());
        }
    }

    if (irBlockNode->getParentBlock()) {
        for (auto successorBlock : successorsToBranchToParent) {
            if (!successorBlock->hasBranchInstruction() && !successorBlock->hasReturnInstruction()) {
                successorBlock->getBuilder()->get()->CreateBr(
                        irBlockNode->getParentBlock().value()->getLastSuccessorOrSelf()->getBlock()
                );
            }
        }
    }
}