//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-assignment-node.h"

std::shared_ptr<ASTNode> TupleAccessAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access assignment since nodes list is not 2");
    }
    return std::make_shared<ASTTupleAccessAssignmentNode>(
            std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );
}