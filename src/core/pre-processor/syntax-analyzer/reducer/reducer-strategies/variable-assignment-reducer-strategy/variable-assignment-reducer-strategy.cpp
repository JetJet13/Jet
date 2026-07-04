//
// Created by Johny Georges on 2024-03-22.
//

#include "variable-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-assignment-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

std::shared_ptr<ASTNode> VariableAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to variable assignment since nodes list is not 2");
    }
    return std::make_shared<ASTVariableAssignmentNode>(
            (std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0]))->getIdentifierNode(),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );
}
