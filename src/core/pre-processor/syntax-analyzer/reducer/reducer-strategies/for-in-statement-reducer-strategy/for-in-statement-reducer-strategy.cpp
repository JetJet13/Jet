//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

std::shared_ptr<ASTNode> ForInStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to for-in statement since nodes list is not 5");
    }

    return std::make_shared<ASTForInStatementNode>(
            std::dynamic_pointer_cast<ASTForNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTForInVariableNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTForInNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTForInSourceNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[4])
    );
}