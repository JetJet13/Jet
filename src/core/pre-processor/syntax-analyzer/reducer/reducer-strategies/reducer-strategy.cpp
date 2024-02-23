//
// Created by Johny Georges on 2024-02-17.
//

#include "reducer-strategy.h"

bool ReducerStrategy::startsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType) {
    if (nodes.empty()) {
        return false;
    }
    return nodes[0]->is(astNodeType);
}

bool ReducerStrategy::endsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType) {
    if (nodes.empty()) {
        return false;
    }
    return nodes[nodes.size() - 1]->is(astNodeType);
}