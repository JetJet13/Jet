//
// Created by Johny Georges on 2026-06-26.
//

#include "module-access-ref-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-ref-assignment-statement-node.h"

ASTNode* ModuleAccessRefAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access ref assignment statement since nodes list is not 2");
    }
    return new ASTModuleAccessRefAssignmentStatementNode(
            (ASTModuleAccessRefAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}