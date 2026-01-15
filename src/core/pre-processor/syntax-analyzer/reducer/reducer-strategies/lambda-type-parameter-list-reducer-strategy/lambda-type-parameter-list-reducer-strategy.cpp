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

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TYPE_NODE)) {
            typeParameterListNode->addParameter((ASTTypeNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            typeParameterListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to lambda type parameter list since node list is malformed");
        }
    }

    return typeParameterListNode;
}