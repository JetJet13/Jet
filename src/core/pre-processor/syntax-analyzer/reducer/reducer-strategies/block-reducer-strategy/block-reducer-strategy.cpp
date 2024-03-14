//
// Created by Johny Georges on 2024-03-14.
//

#include "block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"

ASTNode* BlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto braceNode = new ASTBlockNode();
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (!nodes[i]->is(AST_COMMA_NODE)) {
            braceNode->addContent((ASTExpressionNode*)nodes[i]);
        }
    }
    return braceNode;
}