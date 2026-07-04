//
// Created by Johny Georges on 2024-03-22.
//

#include "variable-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"

std::shared_ptr<ASTNode> VariableAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTVariableAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTVariableAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}
