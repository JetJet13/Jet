//
// Created by Johny Georges on 2025-07-09.
//

#include "lambda-type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-parameter-list-node.h"

ASTNode* LambdaTypeParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto typeParameterListNode = new ASTLambdaTypeParameterListNode(
            (ASTLambdaTypeParameterListStartNode*)nodes[0],
            (ASTLambdaTypeParameterListEndNode*)nodes[nodes.size() - 1]
    );
    for (auto node : nodes) {
        if (node->is(AST_TYPE_NODE)) {
            typeParameterListNode->addParameter((ASTTypeNode*)node);
        }
    }
    return typeParameterListNode;
}