//
// Created by Johny Georges on 2025-07-09.
//

#include "lambda-type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-parameter-list-node.h"

std::shared_ptr<ASTNode> LambdaTypeParameterListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto typeParameterListNode = std::make_shared<ASTLambdaTypeParameterListNode>(
            std::dynamic_pointer_cast<ASTLambdaTypeParameterListStartNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTLambdaTypeParameterListEndNode>(nodes[nodes.size() - 1])
    );

    for (uint64_t i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TYPE_NODE)) {
            typeParameterListNode->addParameter(std::dynamic_pointer_cast<ASTTypeNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            typeParameterListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to lambda type parameter list since node list is malformed");
        }
    }

    return typeParameterListNode;
}