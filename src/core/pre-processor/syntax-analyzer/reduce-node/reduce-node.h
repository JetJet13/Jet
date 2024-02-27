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
    bool _includePrefix;
public:
    ReduceNode(int numReducedNodes, ASTNodeType targetAstNodeType, bool includePrefix);
    ASTNodeType getTargetAstNodeType();
    int getNumReducedNodes();
    bool includePrefix();
};

#endif //JETLANG_REDUCE_NODE_H
