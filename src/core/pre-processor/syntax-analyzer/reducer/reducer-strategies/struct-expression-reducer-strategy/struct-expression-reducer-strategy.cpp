//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"

ASTNode* StructExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto structExpressionNode = new ASTStructExpressionNode((ASTStructStartNode*)nodes[0], (ASTStructEndNode*)nodes[nodes.size() - 1]);
    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_STRUCT_KEY_VALUE_NODE)) {
            structExpressionNode->addKeyValuePair((ASTStructKeyValueNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            structExpressionNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to struct expression since node list is malformed");
        }
    }

    return structExpressionNode;
}