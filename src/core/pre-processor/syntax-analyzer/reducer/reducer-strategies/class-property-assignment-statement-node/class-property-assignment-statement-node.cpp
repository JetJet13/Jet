//
// Created by Johny Georges on 2024-04-25.
//

#include "class-property-assignment-statement-node.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"

std::shared_ptr<ASTNode> ClassPropertyAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var declaration since nodes list is not 2");
    }
    return std::make_shared<ASTClassPropertyAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTClassPropertyAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}