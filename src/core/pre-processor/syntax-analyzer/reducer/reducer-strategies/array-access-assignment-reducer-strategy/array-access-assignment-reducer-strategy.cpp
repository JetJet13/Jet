//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-assignment-node.h"

std::shared_ptr<ASTNode> ArrayAccessAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access assignment since nodes list is not 2");
    }
    return std::make_shared<ASTArrayAccessAssignmentNode>(
            std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );
}