//
// Created by Johny Georges on 2024-02-08.
//

#include "reduce-node.h"

ReduceNode::ReduceNode(int numReducedNodes, ASTNodeType targetAstNodeType) {
    _targetAstNodeType = targetAstNodeType;
    _numReducedNodes = numReducedNodes;
}

ASTNodeType ReduceNode::getTargetAstNodeType() {
    return _targetAstNodeType;
}

int ReduceNode::getNumReducedNodes() {
    return _numReducedNodes;
}