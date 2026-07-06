//
// Created by Johny Georges on 2025-05-19.
//

#include "block-ir-injector-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"

void BlockIRInjectorStrategy::inject(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    for (auto statement : *irBlockNode->getBody()) {
        if (statement->is(IR_IF_STATEMENT_NODE)) {
            auto ifStatement = std::dynamic_pointer_cast<IRIfStatementNode>(statement);
            irBlockNode->getLastChildOrSelf()->getBuilder()->get()->CreateBr(ifStatement->getIfElseNode()->getIfBlock()->getBlock());
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
            ifStatement->getIfElseNode()->nestIn(irBlockNode);
            if (ifStatement->getElseNode()) {
                irBlockNode->nest(ifStatement->getElseNode().value());
            }

            if (!ifStatement->getIfElseNode()->getEndBlock()->hasReturnInstruction() && ifStatement->getIfElseNode()->getEndBlock()->isReachable()) {
                irBlockNode->createChild();
                ifStatement->getIfElseNode()->getEndBlock()->getBuilder()->get()->CreateBr(
                        irBlockNode->getLastChildOrSelf()->getBlock()
                );
                irBlockNode->getLastChildOrSelf()->getBlock()->moveAfter(ifStatement->getIfElseNode()->getEndBlock()->getBlock());
            } else if (ifStatement->getIfElseNode()->getEndBlock()->isUnreachable()) {
                ifStatement->getIfElseNode()->getEndBlock()->addVoidReturn();
            }
        } else if (statement->is(IR_WHILE_STATEMENT_NODE)) {
            auto whileStatement = std::dynamic_pointer_cast<IRWhileStatementNode>(statement);
            irBlockNode->getLastChildOrSelf()->getBuilder()->get()->CreateBr(whileStatement->getWhileBlock()->getBlock());
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
            whileStatement->nestIn(irBlockNode);
            irBlockNode->createChild();
            whileStatement->getEndBlock()->getBuilder()->get()->CreateBr(
                    irBlockNode->getLastChildOrSelf()->getBlock()
            );
            irBlockNode->getLastChildOrSelf()->getBlock()->moveAfter(whileStatement->getEndBlock()->getBlock());
        } else if (statement->is(IR_FOR_IN_STATEMENT_NODE)) {
            auto forInStatement = std::dynamic_pointer_cast<IRForInStatementNode>(statement);
            irBlockNode->getLastChildOrSelf()->getBuilder()->get()->CreateBr(forInStatement->getSetupBlock()->getBlock());
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
            forInStatement->nestIn(irBlockNode);
            irBlockNode->createChild();
            forInStatement->getEndBlock()->getBuilder()->get()->CreateBr(
                    irBlockNode->getLastChildOrSelf()->getBlock()
            );
            irBlockNode->getLastChildOrSelf()->getBlock()->moveAfter(forInStatement->getEndBlock()->getBlock());
        } else if (!irBlockNode->getLastChildOrSelf()->hasReturnInstruction() && !irBlockNode->getLastChildOrSelf()->hasBranchInstruction()) {
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
        }
    }

}