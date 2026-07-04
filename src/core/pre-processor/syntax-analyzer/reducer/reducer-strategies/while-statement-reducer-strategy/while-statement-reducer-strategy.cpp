//
// Created by Johny Georges on 2024-03-29.
//

#include "while-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"

std::shared_ptr<ASTNode> WhileStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to while statement since nodes list is not of size 3");
    }

    return std::make_shared<ASTWhileStatementNode>(
            std::dynamic_pointer_cast<ASTWhileNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowConditionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[2])
    );
}