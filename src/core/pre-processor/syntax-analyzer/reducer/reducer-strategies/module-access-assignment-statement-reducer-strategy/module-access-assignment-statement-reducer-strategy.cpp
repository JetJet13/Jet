//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"

ASTNode* ModuleAccessAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access assignment statement since nodes list is not 2");
    }
    return new ASTModuleAccessAssignmentStatementNode(
            (ASTModuleAccessAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}