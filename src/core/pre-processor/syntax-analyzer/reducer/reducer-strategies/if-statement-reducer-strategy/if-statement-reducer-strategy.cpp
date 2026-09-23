//
// Created by Johny Georges on 2024-03-28.
//

#include "if-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

std::shared_ptr<ASTNode> IfStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.empty()) {
        throw std::logic_error("NO NODES!");
    }
    auto elseIfBlocks = std::vector<std::shared_ptr<ASTElseIfBlockNode>>();
    auto elseBlock = std::optional<std::shared_ptr<ASTElseBlockNode>>();
    for (uint64_t i = 1; i < nodes.size() ; i++) {
        if (nodes[i]->is(AST_ELSE_IF_BLOCK_NODE)) {
            elseIfBlocks.push_back(std::dynamic_pointer_cast<ASTElseIfBlockNode>(nodes[i]));
        }
        if (nodes[i]->is(AST_ELSE_BLOCK_NODE)) {
            elseBlock = std::dynamic_pointer_cast<ASTElseBlockNode>(nodes[i]);
        }
    }

    return std::make_shared<ASTIfStatementNode>(
            std::dynamic_pointer_cast<ASTIfBlockNode>(nodes[0]),
            elseIfBlocks,
            elseBlock
    );
}