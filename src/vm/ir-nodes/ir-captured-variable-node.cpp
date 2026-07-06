//
// Created by Johny Georges on 2026-02-06.
//

#include "ir-captured-variable-node.h"

IRCapturedVariableNode::IRCapturedVariableNode(std::shared_ptr<IRInstructionNode> mallocVariable, std::shared_ptr<IRInstructionNode> arc) {
    _mallocVariable = mallocVariable;
    _arc = arc;
}

std::shared_ptr<IRInstructionNode> IRCapturedVariableNode::getVariable() {
    return _mallocVariable;
}

std::shared_ptr<IRInstructionNode> IRCapturedVariableNode::getArc() {
    return _arc;
}