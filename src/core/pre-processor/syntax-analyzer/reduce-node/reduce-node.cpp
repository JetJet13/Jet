//
// Created by Johny Georges on 2024-02-08.
//

#include "reduce-node.h"

ReduceNode::ReduceNode(int numReducedNodes, ASTNodeType targetAstNodeType, bool includePrefix) {
    _targetAstNodeType = targetAstNodeType;
    _numReducedNodes = includePrefix ? numReducedNodes + 1 : numReducedNodes;
    _includePrefix = includePrefix;
}

ASTNodeType ReduceNode::getTargetAstNodeType() {
    return _targetAstNodeType;
}

int ReduceNode::getNumReducedNodes() {
    return _numReducedNodes;
}

bool ReduceNode::includePrefix() {
    return _includePrefix;
}