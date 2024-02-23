//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_REDUCE_NODE_H
#define JETLANG_REDUCE_NODE_H

#include "../../../ast/ast-nodes/ast-node.h"

class ReduceNode {
private:
    ASTNodeType _targetAstNodeType;
    int _numReducedNodes;
public:
    ReduceNode(int numReducedNodes, ASTNodeType targetAstNodeType);
    ASTNodeType getTargetAstNodeType();
    int getNumReducedNodes();
};

#endif //JETLANG_REDUCE_NODE_H
