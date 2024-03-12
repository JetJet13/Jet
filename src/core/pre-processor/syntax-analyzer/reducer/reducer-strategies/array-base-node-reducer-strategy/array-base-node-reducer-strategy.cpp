//
// Created by Johny Georges on 2024-03-09.
//

#include "array-base-node-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-base-nodes/ast-array-base-node.h"


ASTNode* ArrayBaseNodeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto arrayBaseNode = new ASTArrayBaseNode();
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (!nodes[i]->is(AST_COMMA_NODE)) {
            arrayBaseNode->addElement((ASTExpressionNode*)nodes[i]);
        }
    }
    return arrayBaseNode;
}