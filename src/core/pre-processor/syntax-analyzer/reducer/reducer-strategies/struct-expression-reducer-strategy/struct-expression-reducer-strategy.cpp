//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"

ASTNode* StructExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {

    auto structExpressionNode = new ASTStructExpressionNode();
    for (auto node: nodes) {
        if (node->is(AST_STRUCT_KEY_VALUE_NODE)) {
            structExpressionNode->addKeyValuePair((ASTStructKeyValueNode*)node);
        }
    }
    return structExpressionNode;
}