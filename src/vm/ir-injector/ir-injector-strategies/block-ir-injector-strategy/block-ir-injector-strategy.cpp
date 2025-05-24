//
// Created by Johny Georges on 2025-05-19.
//

#include "block-ir-injector-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"

void BlockIRInjectorStrategy::inject(IRBlockNode* irBlockNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto successorsToBranchToParent = std::vector<IRBlockNode*>();
    for (auto statement : *irBlockNode->getBody()) {
        if (statement->is(IR_IF_STATEMENT_NODE)) {
            auto ifStatement = (IRIfStatementNode*)statement;
            irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(ifStatement->getIfElseNode()->getIfBlock()->getBlock());
            ifStatement->getIfElseNode()->setBlocksToBeSuccessorsOf(irBlockNode);
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, scope);
            irBlockNode->createSuccessor();
            successorsToBranchToParent.push_back(irBlockNode->getLastSuccessorOrSelf());
            ifStatement->getIfElseNode()->getEndBlock()->getBuilder()->get()->CreateBr(
                irBlockNode->getLastSuccessorOrSelf()->getBlock()
            );
        } else if (statement->is(IR_WHILE_STATEMENT_NODE)) {
            auto whileStatement = (IRWhileStatementNode*)statement;
            irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateBr(whileStatement->getWhileBlock()->getBlock());
            whileStatement->setBlocksToBeSuccessorsOf(irBlockNode);
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, scope);
            irBlockNode->createSuccessor();
            successorsToBranchToParent.push_back(irBlockNode->getLastSuccessorOrSelf());
            whileStatement->getEndBlock()->getBuilder()->get()->CreateBr(
                    irBlockNode->getLastSuccessorOrSelf()->getBlock()
            );
        } else {
            irInjector->inject(irBlockNode->getLastSuccessorOrSelf(), statement, irModule, scope);
        }
    }

    if (irBlockNode->getParentBlock()) {
        for (auto successorBlock : successorsToBranchToParent) {
            if (!successorBlock->hasBranchStatement()) {
                successorBlock->getBuilder()->get()->CreateBr(
                        irBlockNode->getParentBlock().value()->getLastSuccessorOrSelf()->getBlock()
                );
            }
        }
    }
}