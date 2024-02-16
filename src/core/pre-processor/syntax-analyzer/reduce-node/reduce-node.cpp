//
// Created by Johny Georges on 2024-02-08.
//

#include "reduce-node.h"

ReduceNode::ReduceNode(int numReducedNodes) {
    _numReducedNodes = numReducedNodes;
}

int ReduceNode::getNumReducedNodes() {
    return _numReducedNodes;
}