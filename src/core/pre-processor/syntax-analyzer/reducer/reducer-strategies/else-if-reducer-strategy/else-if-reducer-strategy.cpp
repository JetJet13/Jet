//
// Created by Johny Georges on 2024-03-28.
//

#include "else-if-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-if-node.h"

std::shared_ptr<ASTNode> ElseIfReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to else if since nodes list is not of size 2");
    }

    return std::make_shared<ASTElseIfNode>(
            std::dynamic_pointer_cast<ASTElseNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTIfNode>(nodes[1])
    );
}