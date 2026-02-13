//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-print-statement-node.h"

IRStatementNode* PrintStatementIRStrategy::generate(ASTPrintStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    // TODO - remove, no longer needed

    return new IRPrintStatementNode(node, arguments, irGenerator->generateChar('\n'), irGenerator->generateChar(' '));
}