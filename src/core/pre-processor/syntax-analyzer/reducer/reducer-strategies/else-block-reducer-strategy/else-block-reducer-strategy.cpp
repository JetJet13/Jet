//
// Created by Johny Georges on 2024-03-28.
//

#include "else-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-block-node.h"

std::shared_ptr<ASTNode> ElseBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to else block since nodes list is not of size 2");
    }

    return std::make_shared<ASTElseBlockNode>(
            std::dynamic_pointer_cast<ASTElseNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[1])
    );
}