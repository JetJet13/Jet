//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"

ASTNode* StructExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1 || !nodes[0]->is(AST_BLOCK_NODE)) {
        throw std::invalid_argument("unable to reduce to struct expression node since node list != 1 or nodes[0] is not an instance of brace node");
    }
    auto braceNode = (ASTBlockNode*)nodes[0];
    auto structExpressionNode = new ASTStructExpressionNode();
    for (auto content: braceNode->getContents()) {
        if (!content->is(AST_STRUCT_KEY_VALUE_NODE)) {
            throw std::invalid_argument("unable to reduce to struct expression node since one or more content values are not an instance of struct key value node");
        }
        structExpressionNode->addKeyValuePair((ASTStructKeyValueNode*)content);
    }
    return structExpressionNode;
}