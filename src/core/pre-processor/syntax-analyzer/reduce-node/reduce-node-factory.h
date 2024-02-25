//
// Created by Johny Georges on 2024-02-24.
//

#ifndef JETLANG_REDUCE_NODE_FACTORY_H
#define JETLANG_REDUCE_NODE_FACTORY_H

#include "../handle/handle.h"
#include "reduce-node.h"

class ReduceNodeFactory {
public:
    static ReduceNode* create(Handle handle, int numNodesToReduce, ASTNodeType targetAstNodeType);
};

#endif //JETLANG_REDUCE_NODE_FACTORY_H
