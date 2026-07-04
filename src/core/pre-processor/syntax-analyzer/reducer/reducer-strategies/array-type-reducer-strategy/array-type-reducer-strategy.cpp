//
// Created by Johny Georges on 2024-04-09.
//

#include "array-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> ArrayTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to array type since nodes list is not of size 3");
    }

    return ASTTypeNodeFactory::createArrayTypeNode(
            std::make_shared<ASTArrayTypeNode>(
                std::dynamic_pointer_cast<ASTArrayTypeStartNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTArrayTypeEndNode>(nodes[2])
            )
    );
}