//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-module-access-assignment-statement-node.h"

std::shared_ptr<ASTNode> ModuleAccessAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTModuleAccessAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTModuleAccessAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}