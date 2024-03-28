//
// Created by Johny Georges on 2024-03-28.
//

#include "control-flow-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-control-flow-statement-node.h"

ASTNode* ControlFlowStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto elseIfBlocks = std::vector<ASTElseIfBlockNode*>();
    auto elseBlock = std::optional<ASTElseBlockNode*>();
    for (int i = 1; i < nodes.size() ; i++) {
        if (nodes[i]->is(AST_ELSE_IF_BLOCK_NODE)) {
            elseIfBlocks.push_back((ASTElseIfBlockNode*)nodes[i]);
        }
        if (nodes[i]->is(AST_ELSE_BLOCK_NODE)) {
            elseBlock = (ASTElseBlockNode*)nodes[i];
        }
    }

    return new ASTControlFlowStatementNode(
            (ASTIfBlockNode*)nodes[0],
            elseIfBlocks,
            elseBlock
    );
}