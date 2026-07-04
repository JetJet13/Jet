//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"

std::shared_ptr<ASTNode> ObjectAccessAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTObjectAccessAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTObjectAccessAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}