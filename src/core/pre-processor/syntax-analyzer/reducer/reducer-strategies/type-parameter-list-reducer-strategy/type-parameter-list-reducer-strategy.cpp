//
// Created by Johny Georges on 2024-04-04.
//

#include "type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-parameter-list-node.h"


std::shared_ptr<ASTNode> TypeParameterListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto typeParameterListNode = std::make_shared<ASTTypeParameterListNode>(
        std::dynamic_pointer_cast<ASTTypeParameterListStartNode>(nodes[0]),
        std::dynamic_pointer_cast<ASTTypeParameterListEndNode>(nodes[nodes.size() - 1])
    );

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TYPE_NODE)) {
            typeParameterListNode->addParameter(std::dynamic_pointer_cast<ASTTypeNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            typeParameterListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to type parameter list since node list is malformed");
        }
    }

    return typeParameterListNode;
}