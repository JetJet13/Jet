//
// Created by Johny Georges on 2024-03-09.
//

#include "array-node-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"


std::shared_ptr<ASTNode> ArrayNodeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto arrayNode = std::make_shared<ASTArrayNode>(std::dynamic_pointer_cast<ASTLeftBracketNode>(nodes[0]), std::dynamic_pointer_cast<ASTRightBracketNode>(nodes[nodes.size() - 1]));

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->isExpression()) {
            arrayNode->addElement(std::dynamic_pointer_cast<ASTExpressionNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            arrayNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to array node since node list is malformed");
        }
    }
    return arrayNode;
}