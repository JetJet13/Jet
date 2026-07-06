//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_IR_CAPTURED_VARIABLE_NODE_H
#define JETLANG_IR_CAPTURED_VARIABLE_NODE_H

#include "ir-instruction-node.h"

class IRCapturedVariableNode {
private:
    std::shared_ptr<IRInstructionNode> _mallocVariable;
    std::shared_ptr<IRInstructionNode> _arc;
public:
    IRCapturedVariableNode(std::shared_ptr<IRInstructionNode> mallocVariable, std::shared_ptr<IRInstructionNode> arc);
    std::shared_ptr<IRInstructionNode> getVariable();
    std::shared_ptr<IRInstructionNode> getArc();
};

#endif //JETLANG_IR_CAPTURED_VARIABLE_NODE_H
