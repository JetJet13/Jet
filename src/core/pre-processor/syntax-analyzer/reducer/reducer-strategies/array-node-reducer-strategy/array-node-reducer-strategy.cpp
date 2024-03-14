//
// Created by Johny Georges on 2024-03-09.
//

#include "array-node-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"


ASTNode* ArrayNodeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto arrayNode = new ASTArrayNode();
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (!nodes[i]->is(AST_COMMA_NODE)) {
            arrayNode->addElement((ASTExpressionNode*)nodes[i]);
        }
    }
    return arrayNode;
}