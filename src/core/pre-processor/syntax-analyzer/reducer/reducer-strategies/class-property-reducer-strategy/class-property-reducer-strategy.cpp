//
// Created by Johny Georges on 2024-04-20.
//

#include "class-property-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-node.h"

ASTNode* ClassPropertyReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTClassPropertyNode(
                (ASTClassPropertyInitNode*)nodes[0],
                this->createExpressionNode(nodes[1])
        );
    }

    if (nodes.size() == 1) {
        return new ASTClassPropertyNode(
                (ASTClassPropertyInitNode*)nodes[0]
        );
    }
    throw std::invalid_argument("unable to reduce to class property since nodes list size is not 2 or 1");

}