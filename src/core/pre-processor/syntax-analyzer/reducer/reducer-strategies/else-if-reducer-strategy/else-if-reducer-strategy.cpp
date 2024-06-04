//
// Created by Johny Georges on 2024-03-28.
//

#include "else-if-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-if-node.h"

ASTNode* ElseIfReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to else if since nodes list is not of size 2");
    }

    return new ASTElseIfNode(
            (ASTElseNode*)nodes[0],
            (ASTIfNode*)nodes[1]
    );
}