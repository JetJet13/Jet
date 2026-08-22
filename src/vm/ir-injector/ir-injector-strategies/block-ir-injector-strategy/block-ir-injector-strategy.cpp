//
// Created by Johny Georges on 2025-05-19.
//

#include "block-ir-injector-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"

void BlockIRInjectorStrategy::inject(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    for (auto statement : *irBlockNode->getBody()) {
        if (statement->isOneOf({ IR_IF_STATEMENT_NODE, IR_WHILE_STATEMENT_NODE, IR_FOR_IN_STATEMENT_NODE })) {
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
        } else if (!irBlockNode->getLastChildOrSelf()->hasReturnInstruction() && !irBlockNode->getLastChildOrSelf()->hasBranchInstruction()) {
            irInjector->inject(irBlockNode->getLastChildOrSelf(), statement, irModule,
                               irBlockNode->getLastChildOrSelf()->getScope());
        }
    }
}