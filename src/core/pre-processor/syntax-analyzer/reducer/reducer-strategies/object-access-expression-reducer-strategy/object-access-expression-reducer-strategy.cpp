//
// Created by Johny Georges on 2024-03-14.
//

#include "object-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

std::shared_ptr<ASTNode> ObjectAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to object access expression since nodes list is too short");
    }

    return std::make_shared<ASTObjectAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTObjectAccessSourceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTPeriodNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTObjectAccessTargetNode>(nodes[2])
    );
}