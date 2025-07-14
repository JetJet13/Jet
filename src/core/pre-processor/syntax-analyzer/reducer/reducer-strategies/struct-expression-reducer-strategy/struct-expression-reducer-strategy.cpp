//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

ASTNode* StructExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    Logger::log("new ASTStructExpressionNode");
    auto structExpressionNode = new ASTStructExpressionNode((ASTStructStartNode*)nodes[0], (ASTStructEndNode*)nodes[nodes.size() - 1]);
    for (auto node: nodes) {
        if (node->is(AST_STRUCT_KEY_VALUE_NODE)) {
            structExpressionNode->addKeyValuePair((ASTStructKeyValueNode*)node);
        }
        if (node->is(AST_COMMA_NODE)) {
            structExpressionNode->addComma((ASTCommaNode*)node);
        }
    }
    return structExpressionNode;
}