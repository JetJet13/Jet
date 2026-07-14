//
// Created by Johny Georges on 2026-07-11.
//

#include "shared-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> SharedTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to shared type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createSharedTypeNode(
            std::make_shared<ASTSharedTypeNode>(
                std::dynamic_pointer_cast<ASTSharedNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTTypeParameterListNode>(nodes[1])
            )
    );
}