//
// Created by Johny Georges on 2024-04-02.
//

#include "try-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-block-node.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"

std::shared_ptr<ASTNode> TryStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {

    if (nodes.size() == 3) {
        return std::make_shared<ASTTryStatementNode>(
                std::dynamic_pointer_cast<ASTTryBlockNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTCatchBlockNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTFinallyBlockNode>(nodes[2])
        );
    }

    if (nodes.size() == 2) {
        return std::make_shared<ASTTryStatementNode>(
                std::dynamic_pointer_cast<ASTTryBlockNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTCatchBlockNode>(nodes[1])
        );
    }

    throw std::invalid_argument("unable to reduce to try statement since nodes list is not of size 2 or 3");
}