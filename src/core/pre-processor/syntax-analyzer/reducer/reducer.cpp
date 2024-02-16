//
// Created by Johny Georges on 2024-02-08.
//

#include "reducer.h"
#include "../../../ast/ast-nodes/ast-symbol-node.h"

ASTNode* Reducer::reduce(Handle handle, ReduceNode* reduceNode) {
    if (handle.isEmpty()) {
        throw std::invalid_argument("handle cannot be empty");
    }

    if (reduceNode->getNumReducedNodes() == 1) {
        return handle.at(0).value();
    }

    auto nodesToReduce = handle.getFirstNodes(reduceNode->getNumReducedNodes());

    return this->generateASTNode(
            this->determineReducedAstNodeType(nodesToReduce),
            nodesToReduce
    );
}

ASTNodeType Reducer::determineReducedAstNodeType(std::vector<ASTNode*> nodes) {
    return AST_EXPRESSION_NODE;
}

ASTNode* Reducer::generateASTNode(ASTNodeType astNodeType, std::vector<ASTNode*> nodes) {
    return nodes[0];
}