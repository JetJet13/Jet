//
// Created by Johny Georges on 2025-02-07.
//

#include "ref-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> RefTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to ref type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createRefTypeNode(
            std::make_shared<ASTRefTypeNode>(
                std::dynamic_pointer_cast<ASTRefTypeKeywordNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTTypeParameterListNode>(nodes[1])
            )
    );
}