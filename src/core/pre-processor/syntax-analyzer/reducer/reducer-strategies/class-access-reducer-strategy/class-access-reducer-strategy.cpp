//
// Created by Johny Georges on 2024-04-25.
//

#include "class-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-access-node.h"

std::shared_ptr<ASTNode> ClassAccessReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class access since nodes list is not 2");
    }

    return std::make_shared<ASTClassAccessNode>(
            std::dynamic_pointer_cast<ASTThisNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTThisAccessNode>(nodes[1])
    );
}