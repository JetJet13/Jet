//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"

ASTNode* ObjectAccessAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access assignment statement since nodes list is not 2");
    }
    return new ASTObjectAccessAssignmentStatementNode(
            (ASTObjectAccessAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}