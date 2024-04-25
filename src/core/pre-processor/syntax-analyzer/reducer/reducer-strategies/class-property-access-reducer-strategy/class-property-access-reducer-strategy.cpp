//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"

ASTNode* ClassPropertyAccessReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property access since nodes list is not 2");
    }
    return new ASTClassPropertyAccessNode(
            ((ASTClassPropertyNameNode*)nodes[1])
    );
}