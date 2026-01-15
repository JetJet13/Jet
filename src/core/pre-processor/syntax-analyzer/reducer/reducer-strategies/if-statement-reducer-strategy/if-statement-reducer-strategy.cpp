//
// Created by Johny Georges on 2024-03-28.
//

#include "if-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

ASTNode* IfStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.empty()) {
        throw std::logic_error("NO NODES!");
    }
    auto elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    auto elseBlock = std::optional<ASTElseBlockNode*>();
    for (unsigned long i = 1; i < nodes.size() ; i++) {
        if (nodes[i]->is(AST_ELSE_IF_BLOCK_NODE)) {
            elseIfBlocks.push_back((ASTElseIfBlockNode*)nodes[i]);
        }
        if (nodes[i]->is(AST_ELSE_BLOCK_NODE)) {
            elseBlock = (ASTElseBlockNode*)nodes[i];
        }
    }

    return new ASTIfStatementNode(
            (ASTIfBlockNode*)nodes[0],
            elseIfBlocks,
            elseBlock
    );
}