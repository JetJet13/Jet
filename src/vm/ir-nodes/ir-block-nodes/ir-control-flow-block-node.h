//
// Created by Johny Georges on 2025-11-24.
//

#ifndef JETLANG_IR_CONTROL_FLOW_BLOCK_NODE_H
#define JETLANG_IR_CONTROL_FLOW_BLOCK_NODE_H

#include "ir-block-node.h"

class IRControlFlowBlockNode : public IRBlockNode {
    using IRBlockNode::IRBlockNode;
public:
    std::vector<IRExpressionNode*>* getExpressionsToFree() override;
    std::vector<IRVariableDeclarationNode*>* getVariablesToFree() override;
    void setInsertionPointBeforeLastInstruction() override;
};

#endif //JETLANG_IR_CONTROL_FLOW_BLOCK_NODE_H
