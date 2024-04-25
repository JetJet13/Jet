//
// Created by Johny Georges on 2024-04-25.
//

#include "class-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-access-node.h"

ASTNode* ClassAccessReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class access since nodes list is not 2");
    }

    return new ASTClassAccessNode(
            (ASTThisNode*)nodes[0],
            (ASTThisAccessNode*)nodes[1]
    );
}