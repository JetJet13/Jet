//
// Created by Johny Georges on 2026-02-06.
//

#include "ir-captured-variable-node.h"

IRCapturedVariableNode::IRCapturedVariableNode(IRInstructionNode* mallocVariable, IRInstructionNode* arc) {
    _mallocVariable = mallocVariable;
    _arc = arc;
}

IRInstructionNode* IRCapturedVariableNode::getVariable() {
    return _mallocVariable;
}

IRInstructionNode* IRCapturedVariableNode::getArc() {
    return _arc;
}