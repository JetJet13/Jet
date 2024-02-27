//
// Created by Johny Georges on 2024-02-24.
//

#include "reduce-node-factory.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"


ReduceNode* ReduceNodeFactory::create(Handle handle, int numNodesToReduce, ASTNodeType targetAstNodeType, bool includePrefix) {
    auto lastNode = handle.at(numNodesToReduce - 1).value();

    return new ReduceNode(numNodesToReduce, targetAstNodeType, includePrefix);
}