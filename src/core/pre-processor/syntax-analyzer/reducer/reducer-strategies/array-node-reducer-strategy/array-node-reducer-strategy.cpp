//
// Created by Johny Georges on 2024-03-09.
//

#include "array-node-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"


ASTNode* ArrayNodeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto arrayNode = new ASTArrayNode((ASTLeftBracketNode*)nodes[0], (ASTRightBracketNode*)nodes[nodes.size() - 1]);

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->isExpression()) {
            arrayNode->addElement((ASTExpressionNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            arrayNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to array node since node list is malformed");
        }
    }
    return arrayNode;
}