//
// Created by Johny Georges on 2024-04-04.
//

#include "lambda-type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-lambda-nodes/ast-lambda-type-parameter-list-node.h"


ASTNode* LambdaTypeParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto lambdaTypeParameterListNode = new ASTLambdaTypeParameterListNode();
    for (auto node : nodes) {
        if (node->is(AST_TYPE_NODE)) {
            lambdaTypeParameterListNode->addParameter((ASTTypeNode*)node);
        }
    }
    return lambdaTypeParameterListNode;
}